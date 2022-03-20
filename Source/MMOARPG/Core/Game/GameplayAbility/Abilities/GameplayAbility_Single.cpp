// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Single.h"

#include "../../Character/MMOARPGCharacterBase.h"
#include "SimpleComboType.h"

void UGameplayAbility_Single::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Main Logic
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (AMMOARPGCharacterBase* OwnerCharacterBase = Cast<AMMOARPGCharacterBase>(ActorInfo->OwnerActor))
	{
		if (UAbilityTask_PlayMontageAndWait* MontageTask = PlayMontageAndWaitSimple(*FString::FromInt(0))) // play correct combo attack section
		{
			// ...
		}
	}
}
