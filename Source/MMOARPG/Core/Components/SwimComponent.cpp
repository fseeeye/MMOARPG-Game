// Fill out your copyright notice in the Description page of Project Settings.


#include "SwimComponent.h"

#include "../Game/Character/MMOARPGCharacterBase.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>

void USwimComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USwimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner_MovementComponent.IsValid() && Owner_CharacterBase.IsValid())
	{
		if (Owner_MovementComponent->MovementMode == EMovementMode::MOVE_Swimming)
		{
			if (Owner_CharacterBase->GetActionState() == ECharacterActionState::SWIM_STATE) // Main Logic
			{
				// Calc rotation rate
				ResetRotationRate(DeltaTime);
			}
			else 
			{
				Owner_CharacterBase->SwitchActionState(ECharacterActionState::SWIM_STATE);
			}
		}
		else if (Owner_CharacterBase->GetActionState() == ECharacterActionState::SWIM_STATE)
		{
			Owner_CharacterBase->SwitchActionState(ECharacterActionState::SWIM_STATE);
		}
		
	}
}
