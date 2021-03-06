// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOARPGCharacter.h"
//#include "HeadMountedDisplayFunctionLibrary.h"
// Components
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Components/FlyComponent.h"
#include "../../Components/SwimComponent.h"
#include "../../Components/FightComponent.h"

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
	PlayerInputComponent->BindAction("SwitchSpecial", IE_Pressed, this, &AMMOARPGCharacter::SwitchSpecialStateOnServer); // switch to FLY action state

	PlayerInputComponent->BindAction("SpeedUp", IE_Pressed, this, &AMMOARPGCharacter::SwitchSpeedUpOnServer); // switch to speed up when at some state
	PlayerInputComponent->BindAction("SpeedUp", IE_Released, this, &AMMOARPGCharacter::SwitchSpeedUpReleasedOnServer);

	PlayerInputComponent->BindAction("FlyDodgeLeft", IE_Pressed, this, &AMMOARPGCharacter::SwitchDodgeLeft); // switch to dodge left when fast fly
	PlayerInputComponent->BindAction("FlyDodgeRight", IE_Pressed, this, &AMMOARPGCharacter::SwitchDodgeRight); // switch to dodge right when fast fly

	PlayerInputComponent->BindAction("MouseLeftButton", IE_Pressed, this, &AMMOARPGCharacter::MouseLeftPressed); // ability: normal attack
	PlayerInputComponent->BindAction("MouseLeftButton", IE_Released, this, &AMMOARPGCharacter::MouseLeftReleased);

	PlayerInputComponent->BindAction("MouseRightButton", IE_Pressed, this, &AMMOARPGCharacter::MouseRightPressed); // ability: dodge ability
	PlayerInputComponent->BindAction("MouseRightButton", IE_Released, this, &AMMOARPGCharacter::MouseRightReleased);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMMOARPGCharacter::SprintPressed); // ability: sprint ability

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

void AMMOARPGCharacter::SwitchSpecialStateOnServer_Implementation()
{
	SwitchSpecialActionMulticast();
}

void AMMOARPGCharacter::SwitchSpecialActionMulticast_Implementation()
{
	if (UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		if ((CharacterMovementComponent->MovementMode == EMovementMode::MOVE_Walking || CharacterMovementComponent->MovementMode == EMovementMode::MOVE_Swimming)
			&& ActionState != ECharacterActionState::FIGHT_STATE) // TODO
		{
			SwitchActionState(ECharacterActionState::FLY_STATE);

			GetFlyComponent()->ResetFly();

			LastActionState = ActionState;
		}
		else if (ActionState == ECharacterActionState::FIGHT_STATE)
		{
		}
	}
}

void AMMOARPGCharacter::SwitchSpeedUpOnServer_Implementation()
{
	SwitchSpeedUpMulticast();
}

void AMMOARPGCharacter::SwitchSpeedUpReleasedOnServer_Implementation()
{
	SwitchSpeedUpReleasedMulticast();
}

void AMMOARPGCharacter::SwitchSpeedUpMulticast_Implementation()
{
	if (ActionState == ECharacterActionState::FLY_STATE && !GetFlyComponent()->bFast)
	{
		GetFlyComponent()->SwitchFastFly();
	}
	else if (ActionState == ECharacterActionState::SWIM_STATE && !GetSwimComponent()->bFast)
	{
		GetSwimComponent()->SwitchFastSwim();
	}
}

void AMMOARPGCharacter::SwitchSpeedUpReleasedMulticast_Implementation()
{
	if (ActionState == ECharacterActionState::FLY_STATE && GetFlyComponent()->bFast)
	{
		GetFlyComponent()->SwitchFastFly();
	}
	else if (ActionState == ECharacterActionState::SWIM_STATE && GetSwimComponent()->bFast)
	{
		GetSwimComponent()->SwitchFastSwim();
	}
}

void AMMOARPGCharacter::SwitchDodgeLeft_Implementation()
{
	SwitchDodgeLeftMulticast();
}

void AMMOARPGCharacter::SwitchDodgeRight_Implementation()
{
	SwitchDodgeRightMulticast();
}

void AMMOARPGCharacter::SwitchDodgeLeftMulticast_Implementation()
{
	if (ActionState == ECharacterActionState::FLY_STATE)
	{
		GetFlyComponent()->SwitchDodge(EFlyDodgeState::LEFT);
	}
}

void AMMOARPGCharacter::SwitchDodgeRightMulticast_Implementation()
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

void AMMOARPGCharacter::MouseLeftPressed_Implementation()
{
	if (GetActionState() == ECharacterActionState::FIGHT_STATE)
	{
		GetFightComponent()->NormalAttackOnPress();
	}
}

void AMMOARPGCharacter::MouseLeftReleased_Implementation()
{
	GetFightComponent()->NormalAttackOnReleasesd();
}

void AMMOARPGCharacter::MouseRightPressed_Implementation()
{
	GetFightComponent()->CallDodgeAbility();
}

void AMMOARPGCharacter::MouseRightReleased_Implementation()
{

}

void AMMOARPGCharacter::SprintPressed_Implementation()
{
	GetFightComponent()->CallSprintAbility();
}

FSimpleComboAttack* AMMOARPGCharacter::GetComboAttack()
{
	return GetFightComponent()->GetNormalAttackInfo();
}

void AMMOARPGCharacter::AnimSignal(int32 InSignal)
{
	Super::AnimSignal(InSignal);

	if (InSignal == 2)
	{
		GetFightComponent()->NormalAttackOnReset();
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
		else if (ActionState == ECharacterActionState::SWIM_STATE)
		{
			GetSwimComponent()->SwimForwardAxis(Value);
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
