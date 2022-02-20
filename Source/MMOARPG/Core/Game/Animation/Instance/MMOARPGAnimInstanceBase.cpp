// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGAnimInstanceBase.h"

#include "GameFramework/PawnMovementComponent.h"
#include "../../Character/MMOARPGCharacterBase.h"

UMMOARPGAnimInstanceBase::UMMOARPGAnimInstanceBase()
	: bDeath(false), bInAir(false), bFight(false), Speed(0.f)
{
}

void UMMOARPGAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMMOARPGAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AMMOARPGCharacterBase* CharacterBase = Cast<AMMOARPGCharacterBase>(TryGetPawnOwner()))
	{
		// Get forward velocity
		Speed = CharacterBase->GetVelocity().Size();
		// Get is falling (in air)
		bInAir = CharacterBase->GetMovementComponent()->IsFalling();
		// Get is fight from CharacterBase class
		bFight = CharacterBase->IsFight();
	}
}
