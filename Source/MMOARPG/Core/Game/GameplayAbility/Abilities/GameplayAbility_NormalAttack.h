// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MMOARPGGameplayAbility.h"
#include "GameplayAbility_NormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UGameplayAbility_NormalAttack : public UMMOARPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	// What the abilities *does*.
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	virtual void OnCompleted() override;
	virtual void OnBlendOut() override;
	virtual void OnInterrupted() override;
	virtual void OnCancelled() override;
};
