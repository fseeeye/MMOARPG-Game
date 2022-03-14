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
		if (auto CharacterMovementComponent = Cast<UCharacterMovementComponent>(CharacterBase->GetMovementComponent()))
		{
			UpdateAxisSpeed3D(CharacterMovementComponent->MaxFlySpeed);
		}

		// Update Fly Rotation Rate
		RotationRate = CharacterBase->GetFlyComponent()->RotationRate;
		// Update Fly bFast
		bFast = CharacterBase->GetFlyComponent()->bFast;

		// Update Fly Dodge State
		FlyDodgeState = CharacterBase->GetFlyComponent()->FlyDodgeState;
		// Update bLanded
		bLanded = *CharacterBase->GetFlyComponent()->bLanded;
	}
}
