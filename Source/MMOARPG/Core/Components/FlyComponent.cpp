// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyComponent.h"

#include "../Game/Character/MMOARPGCharacterBase.h"
#include <GameFramework/CharacterMovementComponent.h>


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

	Inner_CharacterBase = Cast<AMMOARPGCharacterBase>(GetOwner());
	if (Inner_CharacterBase)
	{
		Inner_MovementComponent = Cast<UCharacterMovementComponent>(Inner_CharacterBase->GetMovementComponent());
	}
}


// Called every frame
void UFlyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFlyComponent::ResetFly()
{
	if (Inner_CharacterBase && Inner_MovementComponent)
	{
		// Set `bOrientRotationToMovement` and flying mode
		if (Inner_CharacterBase->GetActionState() == ECharacterActionState::FLY_STATE)
		{
			Inner_MovementComponent->bOrientRotationToMovement = false;
			Inner_MovementComponent->SetMovementMode(MOVE_Flying);
		}
		else
		{
			Inner_MovementComponent->bOrientRotationToMovement = true;
			Inner_MovementComponent->SetMovementMode(MOVE_Walking);
		}
	}
}

