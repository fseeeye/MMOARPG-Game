// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MMOARPGGameplayAbility.h"
#include "GameplayAbility_Base.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UGameplayAbility_Base : public UMMOARPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void OnCompleted() override;
	virtual void OnBlendOut() override;
	virtual void OnInterrupted() override;
	virtual void OnCancelled() override;
};
