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
			FRotator CameraRotation = Owner_CameraComponent->GetComponentRotation();
			FRotator CapsuleRotation = Owner_CapsuleComponent->GetComponentRotation();
			FRotator NewRotation = FMath::RInterpTo(CapsuleRotation, CameraRotation, DeltaTime, 8.f); // Calc new interp Capsule Rotation depends on Camera Rotation
			Owner_CharacterBase->SetActorRotation(NewRotation);

			// Calc fly rotation rate (map angular velocity)
			//FVector AngularVelocity = Owner_CapsuleComponent->GetPhysicsAngularVelocityInDegrees();
			//DebugPrint(DeltaTime, AngularVelocity.ToString());
			float FramesPerSecond = 1.f / DeltaTime;
			FRotator RotationDiff = NewRotation - LastRotation;
			RotationDiff *= FramesPerSecond;
			DebugPrint(DeltaTime, RotationDiff.ToString());
			FlyRotationRate.X = FMath::GetMappedRangeValueClamped(FVector2D(-360.f, 360.f), FVector2D(-1.f, 1.f), RotationDiff.Yaw); // Map angular velocity to (-1, 1)

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
			Owner_MovementComponent->bOrientRotationToMovement = true;
			Owner_MovementComponent->SetMovementMode(MOVE_Walking);
		}
	}
}

