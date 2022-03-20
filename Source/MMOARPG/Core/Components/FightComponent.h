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
		ABILITY
	};
	
public:
	UFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*** Ability Utils ***/
public:
	void AddInherentAbility(const FName& InAbilityName, EAbilityType InAbilityType = EAbilityType::ABILITY);

	UMMOARPGGameplayAbility* FindAbility(const FName& InAbilityName);

	UFUNCTION(BlueprintCallable)
	void CallFightAbility(const FName& InAbilityName);

protected:
	FGameplayAbilitySpecHandle AddAbility(TSubclassOf<UGameplayAbility> InNewAbility);

protected:
	TMap<FName, FGameplayAbilitySpecHandle> CharacterAbilities;

	/*** Ability: Normal Attack ***/
public:
	UFUNCTION(NetMulticast, Reliable)
	void NormalAttackOnPress();

	UFUNCTION(NetMulticast, Reliable)
	void NormalAttackOnReleasesd();

	UFUNCTION(NetMulticast, Reliable)
	void NormalAttackOnReset();

	FORCEINLINE FSimpleComboAttack* GetNormalAttackInfo() { return &NormalAttackInfo; }

protected:
	void RegisterComboAttack(FSimpleComboAttack& InComboAttack, const FName& InAbilityName);

	/*** Ability: Dodge ***/
public:
	UFUNCTION(NetMulticast, Reliable)
	void CallDodgeAbility();

	/*** Ability: Sprint ***/
public:
	UFUNCTION(NetMulticast, Reliable)
	void CallSprintAbility();

};
