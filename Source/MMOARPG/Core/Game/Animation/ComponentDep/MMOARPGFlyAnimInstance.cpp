// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGFlyAnimInstance.h"

#include "../../Character/MMOARPGCharacterBase.h"

// Components
#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "../../../Components/FlyComponent.h"

UMMOARPGFlyAnimInstance::UMMOARPGFlyAnimInstance()
	: Super()
	, FlyDodgeState(EFlyDodgeState::NONE)
{

}

void UMMOARPGFlyAnimInstance::InitAnimInstance(ACharacter* InCharacter)
{
	Super::InitAnimInstance(InCharacter);

}

void UMMOARPGFlyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
}

void UMMOARPGFlyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AMMOARPGCharacterBase* CharacterBase = Cast<AMMOARPGCharacterBase>(TryGetPawnOwner()))
	{
		// Update Fly Speed
		FVector  CurrentSpeed = CharacterBase->GetVelocity();
		FRotator CurrentRotation = CharacterBase->GetActorRotation();
		CurrentSpeed = CurrentRotation.UnrotateVector(CurrentSpeed); // fix speed by rotation matrix

		if (auto CharacterMovementComponent = Cast<UCharacterMovementComponent>(CharacterBase->GetMovementComponent()))
		{
			float MaxFlySpeed = CharacterMovementComponent->MaxFlySpeed;

			// Map current speed to (-1, 1)
			FlySpeed.X = FMath::GetMappedRangeValueClamped(FVector2D(-MaxFlySpeed, MaxFlySpeed), FVector2D(-1, 1), CurrentSpeed.X);
			FlySpeed.Y = FMath::GetMappedRangeValueClamped(FVector2D(-MaxFlySpeed, MaxFlySpeed), FVector2D(-1, 1), CurrentSpeed.Y);
			FlySpeed.Z = FMath::GetMappedRangeValueClamped(FVector2D(-MaxFlySpeed, MaxFlySpeed), FVector2D(-1, 1), CurrentSpeed.Z);
		}

		// Update Fly Rotation
		FlyRotationRate = CharacterBase->GetFlyComponent()->FlyRotationRate;
		// Update Fly Dodge State
		FlyDodgeState = CharacterBase->GetFlyComponent()->FlyDodgeState;
		// Update bFastFly
		bFastFly = *CharacterBase->GetFlyComponent()->bFastFly;
		// Update bLanded
		bLanded = *CharacterBase->GetFlyComponent()->bLanded;
	}
}
