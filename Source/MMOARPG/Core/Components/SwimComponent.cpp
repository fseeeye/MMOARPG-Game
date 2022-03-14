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
				// Lock View ( character turn to camera direction )
				LockView(DeltaTime, true);

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

void USwimComponent::SwimForwardAxis(float InAxisValue)
{
	if (Owner_CharacterBase.IsValid() && Owner_MovementComponent.IsValid() && Owner_CapsuleComponent.IsValid() && Owner_CameraComponent.IsValid())
	{
		if (InAxisValue >= 0.f) // ban backward
		{
			const FVector Direction = Owner_CameraComponent->GetForwardVector(); // get forward vector
			Owner_CharacterBase->AddMovementInput(Direction, InAxisValue); // impl axis value at forward direction
		}
	}
}

void USwimComponent::SwitchFastSwim()
{
	if (Owner_MovementComponent.IsValid())
	{
		if (bFast)
		{
			bFast = false;
			Owner_MovementComponent->MaxSwimSpeed = 300.f;
		}
		else
		{
			bFast = true;
			Owner_MovementComponent->MaxSwimSpeed = 600.f;
		}
	}
}
