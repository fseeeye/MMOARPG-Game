// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGCharacterBase.h"

#include "../MMOARPGGameState.h"
#include "../Animation/Instance/MMOARPGAnimInstanceBase.h"

#include <Net/UnrealNetwork.h>
#include <Components/SkeletalMeshComponent.h>


// Sets default values
AMMOARPGCharacterBase::AMMOARPGCharacterBase()
	: bFight(false), SwitchStateAnimTableID(INDEX_NONE)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMMOARPGCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register `bFight` only update for Simulated Player (on other client)
	DOREPLIFETIME_CONDITION(AMMOARPGCharacterBase, bFight, COND_SimulatedOnly);
}

// Called when the game starts or when spawned
void AMMOARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			if (FCharacterAnimTableRow* SwitchStateAnimTR = GameState->GetCharacterAnimTableRow(GetSwitchStateAnimTableID()))
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

void AMMOARPGCharacterBase::AnimSignal(int32 InSignal)
{
	K2_AnimSignal(InSignal);
}

void AMMOARPGCharacterBase::ChangeFightOnServer_Implementation(bool bNewFight)
{
	bFight = bNewFight;
}
