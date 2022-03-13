// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMotionComponent.h"

#include "../Game/Character/MMOARPGCharacterBase.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values for this component's properties
UActorMotionComponent::UActorMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner_CharacterBase = Cast<AMMOARPGCharacterBase>(GetOwner());
	if (Owner_CharacterBase.IsValid())
	{
		Owner_MovementComponent = Cast<UCharacterMovementComponent>(Owner_CharacterBase->GetMovementComponent());
		Owner_CapsuleComponent = Owner_CharacterBase->GetCapsuleComponent();
		Owner_CameraComponent = Owner_CharacterBase->GetFollowCamera();
	}
}


// Called every frame
void UActorMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorMotionComponent::LockView(float DeltaTime, bool bClearPitch /*= false*/)
{
	// Reset Actor rotation
	const FRotator CameraRotation = Owner_CameraComponent->GetComponentRotation();
	const FRotator CapsuleRotation = Owner_CapsuleComponent->GetComponentRotation();

	FRotator NewRotation;
	if (bClearPitch)
	{
		// Calc new interp Capsule Rotation depends on Camera Rotation
		NewRotation = FMath::RInterpTo(CapsuleRotation, FRotator(0.f, CameraRotation.Yaw, CameraRotation.Roll), DeltaTime, 8.f);
	}
	else
	{
		NewRotation = FMath::RInterpTo(CapsuleRotation, CameraRotation, DeltaTime, 8.f);
	}

	Owner_CharacterBase->SetActorRotation(NewRotation);
}

void UActorMotionComponent::ResetRotationRate(float DeltaTime)
{
	// Calc fly rotation rate (map angular velocity)
	//FVector AngularVelocity = Owner_CapsuleComponent->GetPhysicsAngularVelocityInDegrees();
	//DebugPrint(DeltaTime, AngularVelocity.ToString());
	FRotator CurrentRotation = Owner_CharacterBase->GetActorRotation();
	FRotator RotationVelocity = (CurrentRotation - LastRotation) * (1.f / DeltaTime);
	//DebugPrint(DeltaTime, RotationVelocity.ToString());
	RotationRate.X = FMath::GetMappedRangeValueClamped(FVector2D(-360.f, 360.f), FVector2D(-1.f, 1.f), RotationVelocity.Yaw); // Map angular velocity to (-1, 1)
	RotationRate.Y = FMath::GetMappedRangeValueClamped(FVector2D(-360.f, 360.f), FVector2D(-1.f, 1.f), RotationVelocity.Pitch);

	LastRotation = CurrentRotation;
}

