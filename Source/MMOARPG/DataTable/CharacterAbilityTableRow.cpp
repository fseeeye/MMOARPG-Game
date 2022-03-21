#include "CharacterAbilityTableRow.h"

#include "Abilities/GameplayAbility.h"


FCharacterAbilityTableRow::FCharacterAbilityTableRow()
	: CharacterID(INDEX_NONE)
{

}

TSubclassOf<UGameplayAbility>* FCharacterAbilityTableRow::FindComboAttackByTagName(const FName& InTagName)
{
	return ComboAttack.FindByPredicate([&](TSubclassOf<UGameplayAbility> InComboAttack) -> bool
		{
			return InComboAttack.GetDefaultObject()->AbilityTags == FGameplayTagContainer(FGameplayTag::RequestGameplayTag(InTagName));
		});
}

TSubclassOf<UGameplayAbility>* FCharacterAbilityTableRow::FindAbilityAttackByTagName(const FName& InTagName)
{
	return AbilityAttack.FindByPredicate([&](TSubclassOf<UGameplayAbility> InAbilityAttack) -> bool
		{
			return InAbilityAttack.GetDefaultObject()->AbilityTags == FGameplayTagContainer(FGameplayTag::RequestGameplayTag(InTagName));
		});
}
