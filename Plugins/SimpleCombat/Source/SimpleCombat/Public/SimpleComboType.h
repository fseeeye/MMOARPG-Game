#pragma once

#include "CoreMinimal.h"
#include "SimpleComboType.generated.h"

USTRUCT(BlueprintType)
struct SIMPLECOMBAT_API FSimpleComboAttack
{
	GENERATED_USTRUCT_BODY()

	FSimpleComboAttack();

	void OnUpdate();

	void OnPress();

	void OnReleased();

	void OnReset();

public:
	UPROPERTY(EditDefaultsOnly, Category = "ComboAttack")
	bool bLongPress;

	UPROPERTY(EditDefaultsOnly, Category = "ComboAttack")
	bool bShortPress;

	UPROPERTY(EditDefaultsOnly, Category = "ComboAttack")
	int32 ComboIndex; // current index in current attack ability

	UPROPERTY()
	int32 MaxIndex; // total index in current attack ability

	UPROPERTY()
	FName ComboAbilityName; // which attack ability that this combo will trigger

	class ISimpleCombatInterface* OutCharacter;
};