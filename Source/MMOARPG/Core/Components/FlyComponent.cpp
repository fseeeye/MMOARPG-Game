// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyComponent.h"

#include "../Game/Character/MMOARPGCharacterBase.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>


// Sets default values for this component's properties
UFlyComponent::UFlyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlyComponent::BeginPlay()

{
	Super::BeginPlay();

	if (Owner_CharacterBase.IsValid())
	{
		// TMP: reset accleration & braking deceleration
		if (Owner_MovementComponent.IsValid())
		{
			Owner_MovementComponent->MaxAcceleration = 2500.f;
			Owner_MovementComponent->BrakingDecelerationFlying = 1400.f;
		}

		// Bind landed delegate
		if (Owner_CapsuleComponent.IsValid())
		{
			Owner_CapsuleComponent->OnComponentHit.AddDynamic(this, &UFlyComponent::OnHitLand);
		}

		// Bind time out delegate
		bDodgeFly.FuncDelegate.BindLambda([&]() { FlyDodgeState = EFlyDodgeState::NONE; });
		bLanded.FuncDelegate.BindLambda([&]() 
			{ 
				if (Owner_CharacterBase.IsValid())
				{
					Owner_CharacterBase->SwitchActionState(ECharacterActionState::NORMAL_STATE);
					ResetFly();
				}
			});
	}
}


// Called every frame
void UFlyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner_CharacterBase.IsValid() && Owner_MovementComponent.IsValid() && Owner_CapsuleComponent.IsValid() && Owner_CameraComponent.IsValid())
	{
		if (Owner_CharacterBase->GetActionState() == ECharacterActionState::FLY_STATE)
		{
			if (Owner_CharacterBase->GetLocalRole() == ROLE_Authority ||
				Owner_CharacterBase->GetLocalRole() == ROLE_AutonomousProxy)
			{
				if (!bLanded)
				{
					// Lock View ( character turn to camera direction )
					LockView(DeltaTime, !bFastFly);

					// Calc rotation rate
					ResetRotationRate(DeltaTime);
				}
			}
		}

		// Tick bool timer
		bDodgeFly.NativeTick(DeltaTime);
		bLanded.NativeTick(DeltaTime);
	}
}

void UFlyComponent::DebugPrint(float InDeltaTime, const FString& InMsg)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, InDeltaTime, FColor::Blue, FString::Printf(TEXT("%s"), *InMsg));
	}
}

void UFlyComponent::ResetFly()
{
	if (Owner_CharacterBase.IsValid() && Owner_MovementComponent.IsValid())
	{
		// Set `bOrientRotationToMovement` and flying mode
		if (Owner_CharacterBase->GetActionState() == ECharacterActionState::FLY_STATE)
		{
			Owner_MovementComponent->bOrientRotationToMovement = false;
			Owner_MovementComponent->SetMovementMode(MOVE_Flying);
		}
		else
		{
			ResetFlyToWalking();
		}

		bFastFly = false;
		bDodgeFly = false;
	}
}

void UFlyComponent::ResetFlyToWalking()
{
	if (Owner_CharacterBase.IsValid() && Owner_MovementComponent.IsValid())
	{
		// reset `bOrientRotationToMovement`
		Owner_MovementComponent->bOrientRotationToMovement = true;
		// reset movement mode
		Owner_MovementComponent->SetMovementMode(MOVE_Walking);
		// reset max fly speed
		Owner_MovementComponent->MaxFlySpeed = 600.f;
		// reset actor pitch rotation
		FRotator CharacterRotation = Owner_CharacterBase->GetActorRotation();
		CharacterRotation.Pitch = 0.f;
		Owner_CharacterBase->SetActorRotation(CharacterRotation);
	}
}

void UFlyComponent::FlyForwardAxis(float InAxisValue)
{
	if (Owner_CharacterBase.IsValid() && Owner_MovementComponent.IsValid() && Owner_CapsuleComponent.IsValid() && Owner_CameraComponent.IsValid())
	{
		if (bFastFly)
		{
			const FVector Direction = Owner_CameraComponent->GetForwardVector(); // get forward vector
			Owner_CharacterBase->AddMovementInput(Direction, 1.f); // keep move forward
		}
		else if (InAxisValue != 0.f)
		{
			const FVector Direction = Owner_CameraComponent->GetForwardVector(); // get forward vector
			Owner_CharacterBase->AddMovementInput(Direction, InAxisValue); // impl axis value at forward direction
		}
	}
}

void UFlyComponent::SwitchFastFly()
{
	if (Owner_MovementComponent.IsValid())
	{
		if (bFastFly)
		{
			bFastFly = false;
			Owner_MovementComponent->MaxFlySpeed = 600.f;
			FlyDodgeState = EFlyDodgeState::NONE;
		}
		else
		{
			bFastFly = true;
			Owner_MovementComponent->MaxFlySpeed = 1200.f;
		}
	}
}

void UFlyComponent::SwitchDodge(EFlyDodgeState InTargetDodge)
{
	if (bFastFly)
	{
		FlyDodgeState = InTargetDodge;
		bDodgeFly = 1.6f;
	}
}

void UFlyComponent::OnHitLand(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Owner_CharacterBase.IsValid() && Owner_CharacterBase->GetActionState() == ECharacterActionState::FLY_STATE && bFastFly)
	{
		// judge angle between forward vector and land normal
		float DotProductRst = FVector::DotProduct(Owner_CapsuleComponent->GetForwardVector(), Hit.ImpactNormal);
		float IncludeAngle = (180.f / PI) * FMath::Acos(DotProductRst);
		if (IncludeAngle >= 120.f && Hit.ImpactNormal.Z > 0.5f) // face land & land isn't a hill
		{
			ResetFlyToWalking();

			bLanded = true;
			bLanded = 1.6f;
		}
	}
}
