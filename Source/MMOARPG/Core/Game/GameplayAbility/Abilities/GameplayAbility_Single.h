// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Base.h"
#include "GameplayAbility_Single.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UGameplayAbility_Single : public UGameplayAbility_Base
{
	GENERATED_BODY()
	
public:
	// What the abilities *does*.
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
