// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGCharacterBase.h"

#include "../MMOARPGGameState.h"
#include "../Animation/Instance/MMOARPGAnimInstanceBase.h"

#include <Net/UnrealNetwork.h>
#include <Components/SkeletalMeshComponent.h>


// Sets default values
AMMOARPGCharacterBase::AMMOARPGCharacterBase()
	: ActionState(ECharacterActionState::NORMAL_STATE)
	, LastActionState(ECharacterActionState::NORMAL_STATE)
	, UserID(INDEX_NONE)
	, CharacterID(INDEX_NONE)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init Character Fly Component
	FlyComponent = CreateDefaultSubobject<UFlyComponent>(TEXT("CharacterFlyComponent"));
	//FlyComponent->SetupAttachment(RootComponent);
}

void AMMOARPGCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register `ActionState` only update for Simulated Player (on other client)
	DOREPLIFETIME_CONDITION(AMMOARPGCharacterBase, ActionState, COND_SimulatedOnly);
}

// Called when the game starts or when spawned
void AMMOARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			if (FCharacterAnimTableRow* SwitchStateAnimTR = GameState->GetCharacterAnimTableRow(GetCharacterID()))
			{
				SwitchStateAnimTableRow = SwitchStateAnimTR;
			}
		}

		// Init FootIK
		if (!GetWorld()->IsServer())
		{
			if (GetMesh())
			{
				if (UMMOARPGAnimInstanceBase* AnimInstanceBase = Cast<UMMOARPGAnimInstanceBase>(GetMesh()->GetAnimInstance()))
				{
					AnimInstanceBase->InitAnimInstance(this);
				}
			}
		}
	}
}

// Called every frame
void AMMOARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMMOARPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMMOARPGCharacterBase::SwitchActionState(ECharacterActionState InTargetActionState)
{
	if (ActionState == InTargetActionState)
	{
		// Switch into normal state
		ActionState = ECharacterActionState::NORMAL_STATE;
	}
	else
	{
		// Switch into target state
		ActionState = InTargetActionState;
	}
}

void AMMOARPGCharacterBase::AnimSignal(int32 InSignal)
{
	K2_AnimSignal(InSignal);
}

void AMMOARPGCharacterBase::ChangeActionStateOnServer_Implementation(ECharacterActionState InActionState)
{
	ActionState = InActionState;
	LastActionState = ActionState;
}
