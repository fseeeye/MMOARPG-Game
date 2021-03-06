#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "GameplayTagContainer.h"

#include "CharacterAbilityTableRow.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FCharacterAbilityTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterAbilityTableRow();

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAbility")
	int32 CharacterID;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAbility")
	TArray<TSubclassOf<UGameplayAbility>> ComboAttack;
	
	UPROPERTY(EditDefaultsOnly, Category = "CharacterAbility")
	TArray<TSubclassOf<UGameplayAbility>> AbilityAttack;

public:
	TSubclassOf<UGameplayAbility>* FindComboAttackByTagName(const FName& InTagName);
	TSubclassOf<UGameplayAbility>* FindAbilityAttackByTagName(const FName& InTagName);
};
