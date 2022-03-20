// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_NormalAttack.h"

#include "../../Character/MMOARPGCharacterBase.h"
#include "SimpleComboType.h"

void UGameplayAbility_NormalAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Main Logic
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (AMMOARPGCharacterBase* OwnerCharacterBase = Cast<AMMOARPGCharacterBase>(ActorInfo->OwnerActor))
	{
		if (UAbilityTask_PlayMontageAndWait* MontageTask = PlayMontageAndWaitSimple(*FString::FromInt(OwnerCharacterBase->GetComboAttack()->ComboIndex))) // play correct combo attack section
		{
			// ...
		}
	}
}
