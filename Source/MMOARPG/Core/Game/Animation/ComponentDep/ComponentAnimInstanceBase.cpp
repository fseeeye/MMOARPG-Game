// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentAnimInstanceBase.h"

#include "../../Character/MMOARPGCharacterBase.h"

// Components
#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "../../../Components/FlyComponent.h"

void UComponentAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UComponentAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
}

void UComponentAnimInstanceBase::UpdateAxisSpeed3D(float InMaxSpeed)
{
	if (AMMOARPGCharacterBase* CharacterBase = Cast<AMMOARPGCharacterBase>(TryGetPawnOwner()))
	{
		// Update Axis Speed
		FVector  CurrentSpeed = CharacterBase->GetVelocity();
		FRotator CurrentRotation = CharacterBase->GetActorRotation();
		CurrentSpeed = CurrentRotation.UnrotateVector(CurrentSpeed); // fix speed by rotation matrix
		// Map current speed to (-1, 1)
		AxisSpeed3D.X = FMath::GetMappedRangeValueClamped(FVector2D(-InMaxSpeed, InMaxSpeed), FVector2D(-1, 1), CurrentSpeed.X);
		AxisSpeed3D.Y = FMath::GetMappedRangeValueClamped(FVector2D(-InMaxSpeed, InMaxSpeed), FVector2D(-1, 1), CurrentSpeed.Y);
		AxisSpeed3D.Z = FMath::GetMappedRangeValueClamped(FVector2D(-InMaxSpeed, InMaxSpeed), FVector2D(-1, 1), CurrentSpeed.Z);
	}
}
