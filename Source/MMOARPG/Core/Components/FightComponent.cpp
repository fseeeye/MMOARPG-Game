// Fill out your copyright notice in the Description page of Project Settings.


#include "FightComponent.h"

#include "../Game/MMOARPGGameState.h"
#include "../Game/GameplayAbility/MMOARPGGameplayAbility.h"


UFightComponent::UFightComponent()
{

}

void UFightComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner_CharacterBase = Cast<AMMOARPGCharacterBase>(GetOwner());
	if (Owner_CharacterBase.IsValid())
	{
		// Register GAS component
		Owner_GASComponent = Cast<UMMOARPGAbilitySystemComponent>(Owner_CharacterBase->GetAbilitySystemComponent());

		if (Owner_CharacterBase->GetLocalRole() == ROLE_Authority) // tip: `GiveAbility()` only allowed on Authority NetRole.
		{
			if (GetWorld())
			{
				// Add Inherent ComboAttacks
				AddInherentAbility(TEXT("NormalAttack"), EAbilityType::COMBOATTACK);

				// Init GAS info
				Owner_GASComponent->InitAbilityActorInfo(Owner_CharacterBase.Get(), Owner_CharacterBase.Get());
			}
		}

		// Register ComboAttack initial info on all NetRole
		RegisterComboAttack(NormalAttackInfo, "NormalAttack");
	}
}

FGameplayAbilitySpecHandle UFightComponent::AddAbility(TSubclassOf<UGameplayAbility> InNewAbility)
{
	if (IsValid(InNewAbility) && Owner_GASComponent.IsValid())
	{
		return Owner_GASComponent->GiveAbility(FGameplayAbilitySpec(InNewAbility));
	}

	return FGameplayAbilitySpecHandle();
}

UMMOARPGGameplayAbility* UFightComponent::FindAbility(const FName& InAbilityName)
{
	if (FGameplayAbilitySpecHandle* Handle = CharacterAbilities.Find(InAbilityName))
	{
		if (Owner_GASComponent.IsValid())
		{
			if (FGameplayAbilitySpec* AbilitySpec = Owner_GASComponent->FindAbilitySpecFromHandle(*Handle))
			{
				return Cast<UMMOARPGGameplayAbility>(AbilitySpec->Ability);
			}
		}
	}

	return nullptr;
}

void UFightComponent::AddInherentAbility(const FName& InAbilityName, EAbilityType InAbilityType /*= EAbilityType::ABILITYATTACK*/)
{
	if (GetWorld())
	{
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			if (FCharacterAbilityTableRow* AbilityTR = GameState->GetCharacterAbilityTableRow(Owner_CharacterBase->GetCharacterID()))
			{
				auto GetInherentAbilityMap = [&](EAbilityType InAbilityType) -> TMap<FName, TSubclassOf<UGameplayAbility>>*
				{
					switch (InAbilityType)
					{
						case EAbilityType::COMBOATTACK: return &AbilityTR->ComboAttack;
						case EAbilityType::ABILITYATTACK: return &AbilityTR->AbilityAttack;
					}

					return nullptr;
				};

				// Add inherent ability
				if (TMap<FName, TSubclassOf<UGameplayAbility>>* InherentAbilityMap = GetInherentAbilityMap(InAbilityType))
				{
					if (TSubclassOf<UGameplayAbility>* NewAbility = InherentAbilityMap->Find(InAbilityName))
					{
						CharacterAbilities.Add(InAbilityName, AddAbility(*NewAbility));
					}
				}
			}
		}
	}
}

void UFightComponent::NormalAttack(const FName& InAbilityName)
{
	if (Owner_GASComponent.IsValid())
	{
		if (FGameplayAbilitySpecHandle* NormalAttackHandle = CharacterAbilities.Find(InAbilityName))
		{
			Owner_GASComponent->TryActivateAbility(*NormalAttackHandle);
		}
	}
}

void UFightComponent::NormalAttackOnPress_Implementation()
{
	NormalAttackInfo.OnPress();
}

void UFightComponent::NormalAttackOnReleasesd_Implementation()
{
	NormalAttackInfo.OnReleased();
}

void UFightComponent::NormalAttackOnReset_Implementation()
{
	NormalAttackInfo.OnReset();
}

void UFightComponent::RegisterComboAttack(FSimpleComboAttack& InComboAttack, const FName& InAbilityName)
{
	InComboAttack.OutCharacter = Owner_CharacterBase.Get();
	InComboAttack.ComboAbilityName = InAbilityName;
	if (UMMOARPGGameplayAbility* GameplayAbility = FindAbility(InAbilityName))
	{
		InComboAttack.MaxIndex = GameplayAbility->GetMontageCompositeSectionsNum();
	}
	else
	{
		InComboAttack.MaxIndex = 0;
	}
}
