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

