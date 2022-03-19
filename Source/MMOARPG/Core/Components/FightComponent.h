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
	FSimpleComboAttack NormalAttackInfo;

	enum class EAbilityType : uint8
	{
		COMBOATTACK,
		ABILITYATTACK
	};
	
public:
	UFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*** Ability Utils ***/
public:
	UMMOARPGGameplayAbility* FindAbility(const FName& InAbilityName);

	void AddInherentAbility(const FName& InAbilityName, EAbilityType InAbilityType = EAbilityType::ABILITYATTACK);

protected:
	FGameplayAbilitySpecHandle AddAbility(TSubclassOf<UGameplayAbility> InNewAbility);

protected:
	TMap<FName, FGameplayAbilitySpecHandle> CharacterAbilities;

	/*** Attack ***/
public:
	UFUNCTION(BlueprintCallable)
	void NormalAttack(const FName& InAbilityName);

	FORCEINLINE FSimpleComboAttack* GetNormalAttackInfo() { return &NormalAttackInfo; }

protected:
	void RegisterComboAttack(FSimpleComboAttack& InComboAttack, const FName& InAbilityName);
};
