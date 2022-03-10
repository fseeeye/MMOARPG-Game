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

	bFastFly = false;
}


// Called when the game starts
void UFlyComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner_CharacterBase = Cast<AMMOARPGCharacterBase>(GetOwner());
	if (Owner_CharacterBase.IsValid())
	{
		Owner_MovementComponent = Cast<UCharacterMovementComponent>(Owner_CharacterBase->GetMovementComponent());
		Owner_CapsuleComponent  = Owner_CharacterBase->GetCapsuleComponent();
		Owner_CameraComponent   = Owner_CharacterBase->GetFollowCamera();
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
			// Reset Actor rotation
			const FRotator CameraRotation = Owner_CameraComponent->GetComponentRotation();
			const FRotator CapsuleRotation = Owner_CapsuleComponent->GetComponentRotation();
			FRotator NewRotation;
			if (!bFastFly)
			{
				// Calc new interp Capsule Rotation depends on Camera Rotation
				NewRotation = FMath::RInterpTo(CapsuleRotation, FRotator(0.f, CameraRotation.Yaw, CameraRotation.Roll), DeltaTime, 8.f);
			}
			else
			{
				NewRotation = FMath::RInterpTo(CapsuleRotation, CameraRotation, DeltaTime, 8.f);
			}
			Owner_CharacterBase->SetActorRotation(NewRotation);

			// Calc fly rotation rate (map angular velocity)
			//FVector AngularVelocity = Owner_CapsuleComponent->GetPhysicsAngularVelocityInDegrees();
			//DebugPrint(DeltaTime, AngularVelocity.ToString());
			FRotator RotationVelocity = (NewRotation - LastRotation) * (1.f / DeltaTime);
			//DebugPrint(DeltaTime, RotationVelocity.ToString());
			FlyRotationRate.X = FMath::GetMappedRangeValueClamped(FVector2D(-360.f, 360.f), FVector2D(-1.f, 1.f), RotationVelocity.Yaw); // Map angular velocity to (-1, 1)
			FlyRotationRate.Y = FMath::GetMappedRangeValueClamped(FVector2D(-360.f, 360.f), FVector2D(-1.f, 1.f), RotationVelocity.Pitch);

			LastRotation = NewRotation;
		}
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

		bFastFly = false;
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
		}
		else
		{
			bFastFly = true;
			Owner_MovementComponent->MaxFlySpeed = 1200.f;
		}
	}
}
