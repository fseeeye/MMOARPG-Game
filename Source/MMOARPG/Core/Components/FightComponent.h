// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMotionComponent.h"

#include "../Game/GameplayAbility/MMOARPGAbilitySystemComponent.h"

#include "FightComponent.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UFightComponent : public UActorMotionComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<UMMOARPGAbilitySystemComponent> Owner_GASComponent;
	
public:
	UFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FGameplayAbilitySpecHandle AddAbility(TSubclassOf<UGameplayAbility> InNewAbility);

	UFUNCTION(BlueprintCallable)
	void NormalAttack(const FName& InKey);

protected:
	TMap<FName, FGameplayAbilitySpecHandle> CharacterAbilities;
};
