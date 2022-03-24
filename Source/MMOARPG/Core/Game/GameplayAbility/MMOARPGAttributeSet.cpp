#include "MMOARPGAttributeSet.h"

#include <Net/UnrealNetwork.h>

UMMOARPGAttributeSet::UMMOARPGAttributeSet()
	: Health(100.f)
	, MaxHealth(100.f)
	, Mana(50.f)
	, MaxMana(50.f)
{

}

void UMMOARPGAttributeSet::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// replicated properties
	DOREPLIFETIME(UMMOARPGAttributeSet, Health);
	DOREPLIFETIME(UMMOARPGAttributeSet, MaxHealth);
	DOREPLIFETIME(UMMOARPGAttributeSet, Mana);
	DOREPLIFETIME(UMMOARPGAttributeSet, MaxMana);
}

void UMMOARPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// TODO: Calc to modify attributes.

}

void UMMOARPGAttributeSet::UpdateAttributes(const FMMOARPGCharacterGameplayData& InCGD)
{
	SET_ATTRIBUTE_SIMPLE(Health, InCGD.Health)
	SET_ATTRIBUTE_SIMPLE(MaxHealth, InCGD.MaxHealth)
	SET_ATTRIBUTE_SIMPLE(Mana, InCGD.Mana)
	SET_ATTRIBUTE_SIMPLE(MaxMana, InCGD.MaxMana)
}

void UMMOARPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOARPGAttributeSet, Health, OldValue);
}

void UMMOARPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOARPGAttributeSet, MaxHealth, OldValue);
}

void UMMOARPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOARPGAttributeSet, Mana, OldValue);
}

void UMMOARPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOARPGAttributeSet, MaxMana, OldValue);
}
