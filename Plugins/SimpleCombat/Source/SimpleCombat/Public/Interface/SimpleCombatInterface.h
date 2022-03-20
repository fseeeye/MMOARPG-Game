// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SimpleCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class USimpleCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLECOMBAT_API ISimpleCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	/* Switch State */
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void AnimSignal(int32 InSignal) {}

	/* Combo Attack */
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void CallNormalAttack(const FName& InAbilityName) {}

	//UFUNCTION(BlueprintCallable, Category = "Combat")
	//virtual void ComboAttack(const FName& InNameKey) {}
	
	virtual struct FSimpleComboAttack* GetComboAttack() { return nullptr; }
};
