// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOARPGCharacter.h"
//#include "HeadMountedDisplayFunctionLibrary.h"
// Components
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Components/FlyComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMMOARPGCharacter

AMMOARPGCharacter::AMMOARPGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMMOARPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMMOARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMMOARPGCharacter::MoveRight);

	PlayerInputComponent->BindAction("SwitchFight", IE_Pressed, this, &AMMOARPGCharacter::SwitchFight); // switch to FIGHT action state
	PlayerInputComponent->BindAction("SwitchFly", IE_Pressed, this, &AMMOARPGCharacter::SwitchFly); // switch to FLY action state

	PlayerInputComponent->BindAction("SpeedUp", IE_Pressed, this, &AMMOARPGCharacter::SwitchSpeedUp); // switch to speed up when at some state
	PlayerInputComponent->BindAction("SpeedUp", IE_Released, this, &AMMOARPGCharacter::SwitchSpeedUp);

	PlayerInputComponent->BindAction("FlyDodgeLeft", IE_Pressed, this, &AMMOARPGCharacter::SwitchDodgeLeft); // switch to dodge left when fast fly
	PlayerInputComponent->BindAction("FlyDodgeRight", IE_Pressed, this, &AMMOARPGCharacter::SwitchDodgeRight); // switch to dodge right when fast fly

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMMOARPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMMOARPGCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMMOARPGCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMMOARPGCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMMOARPGCharacter::OnResetVR);
}


void AMMOARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMMOARPGCharacter::OnResetVR()
{
	// If MMOARPG is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in MMOARPG.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMMOARPGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector InLocation)
{
		Jump();
}

void AMMOARPGCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector InLocation)
{
		StopJumping();
}

void AMMOARPGCharacter::SwitchFight()
{
	SwitchActionState(ECharacterActionState::FIGHT_STATE);

	// Play anim montage on local client
	PlayFightMontage();

	// Call Server to change Action State to FIGHT
	ChangeActionStateOnServer(ActionState); // `OnRep_ActionStateChanged` function will be called on other client

	LastActionState = ActionState;
}

void AMMOARPGCharacter::PlayFightMontage()
{
	// Play `Sowrd Draw` or `Sword Putup` Anim Montage slot
	if (FCharacterAnimTableRow* SwitchStateAnimTR = GetCharacterSwitchStateAnimTableRow())
	{
		if (SwitchStateAnimTR->SwitchFightMontage)
		{
			PlayAnimMontage(SwitchStateAnimTR->SwitchFightMontage, 1.f, ActionState == ECharacterActionState::FIGHT_STATE ? TEXT("SwordDraw") : TEXT("SwordPutup"));
		}
	}
}

void AMMOARPGCharacter::SwitchFly()
{
	SwitchActionState(ECharacterActionState::FLY_STATE);

	GetFlyComponent()->ResetFly();

	LastActionState = ActionState;
}

void AMMOARPGCharacter::SwitchSpeedUp()
{
	if (ActionState == ECharacterActionState::FLY_STATE)
	{
		GetFlyComponent()->SwitchFastFly();
	}
}

void AMMOARPGCharacter::SwitchDodgeLeft()
{
	if (ActionState == ECharacterActionState::FLY_STATE)
	{
		GetFlyComponent()->SwitchDodge(EFlyDodgeState::LEFT);
	}
}

void AMMOARPGCharacter::SwitchDodgeRight()
{
	if (ActionState == ECharacterActionState::FLY_STATE)
	{
		GetFlyComponent()->SwitchDodge(EFlyDodgeState::RIGHT);
	}
}

void AMMOARPGCharacter::OnRep_ActionStateChanged()
{
	// Only do on other Client.
	if (GetLocalRole() != ROLE_Authority)
	{
		if (ActionState == ECharacterActionState::FIGHT_STATE || LastActionState == ECharacterActionState::FIGHT_STATE)
		{
			// Play FIGHT anim montage 
			PlayFightMontage();
		}

		LastActionState = ActionState;
	}
}

void AMMOARPGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMMOARPGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMMOARPGCharacter::MoveForward(float Value)
{
	if (Controller != nullptr)
	{
		if (ActionState == ECharacterActionState::FLY_STATE)
		{
			GetFlyComponent()->FlyForwardAxis(Value);
		}
		else if (Value != 0.0f)
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AMMOARPGCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
