// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGSwimAnimInstance.h"

#include "../../Character/MMOARPGCharacterBase.h"

// Components
#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "../../../Components/SwimComponent.h"

void UMMOARPGSwimAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMMOARPGSwimAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AMMOARPGCharacterBase* CharacterBase = Cast<AMMOARPGCharacterBase>(TryGetPawnOwner()))
	{
		if (auto CharacterMovementComponent = Cast<UCharacterMovementComponent>(CharacterBase->GetMovementComponent()))
		{
			UpdateAxisSpeed3D(CharacterMovementComponent->MaxSwimSpeed);
		}

		// Update Swim Rotation Rate
		RotationRate = CharacterBase->GetSwimComponent()->RotationRate; 
	}
}
