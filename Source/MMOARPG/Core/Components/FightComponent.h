// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMotionComponent.h"

#include "../Game/GameplayAbility/MMOARPGAbilitySystemComponent.h"
#include "SimpleComboType.h"

#include "FightComponent.generated.h"

class UMMOARPGGameplayAbility;

/**
 * 
 */
UCLASS()
class MMOARPG_API UFightComponent : public UActorMotionComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<UMMOARPGAbilitySystemComponent> Owner_GASComponent;

	UPROPERTY()
	FSimpleComboAttack ComboAttack;
	
public:
	UFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*** Ability Utils ***/
public:
	FGameplayAbilitySpecHandle AddAbility(TSubclassOf<UGameplayAbility> InNewAbility);
	UMMOARPGGameplayAbility* FindAbility(const FName& InAbilityName);

protected:
	TMap<FName, FGameplayAbilitySpecHandle> CharacterAbilities;

	/*** Attack ***/
public:
	UFUNCTION(BlueprintCallable)
	void NormalAttack(const FName& InAbilityName);

	FORCEINLINE FSimpleComboAttack* GetComboAttack() { return &ComboAttack; }

protected:
	void RegisterComboAttack(FSimpleComboAttack& InComboAttack, const FName& InAbilityName);
};
