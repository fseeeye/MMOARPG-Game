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
			// Add Inherent ComboAttack
			AddInherentAbility(TEXT("Player.Attack.ComboAttack"), EAbilityType::COMBOATTACK);
			// Add Inherent Abilities
			AddInherentAbility(TEXT("Player.Ability.Dodge"), EAbilityType::ABILITY);
			AddInherentAbility(TEXT("Player.Ability.Sprint"), EAbilityType::ABILITY);

			// Init GAS info (tip: only init ability info on authority)
			Owner_GASComponent->InitAbilityActorInfo(Owner_CharacterBase.Get(), Owner_CharacterBase.Get());
		}

		// Register ComboAttack initial info on all NetRole
		RegisterComboAttack(NormalAttackInfo, "Player.Attack.ComboAttack");
	}
}

void UFightComponent::AddInherentAbility(const FName& InAbilityName, EAbilityType InAbilityType /*= EAbilityType::ABILITYATTACK*/)
{
	if (GetWorld())
	{
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			if (FCharacterAbilityTableRow* AbilityTR = GameState->GetCharacterAbilityTableRow(Owner_CharacterBase->GetCharacterID()))
			{
				auto GetInherentAbility = [&](EAbilityType InAbilityType) -> TSubclassOf<UGameplayAbility>*
				{
					switch (InAbilityType)
					{
					case EAbilityType::COMBOATTACK: return AbilityTR->FindComboAttackByTagName(InAbilityName);
					case EAbilityType::ABILITY: return AbilityTR->FindAbilityAttackByTagName(InAbilityName);
					}

					return nullptr;
				};

				// Add inherent ability
				if (TSubclassOf<UGameplayAbility>* InherentAbility = GetInherentAbility(InAbilityType))
				{
					CharacterAbilities.Add(InAbilityName, AddAbility(*InherentAbility));
				}
			}
		}
	}
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

void UFightComponent::CallFightAbility(const FName& InAbilityName)
{
	if (Owner_GASComponent.IsValid())
	{
		if (FGameplayAbilitySpecHandle* NormalAttackHandle = CharacterAbilities.Find(InAbilityName))
		{
			Owner_GASComponent->TryActivateAbility(*NormalAttackHandle);
		}
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
		InComboAttack.MaxIndex = 3; // TODO
	}
}

void UFightComponent::CallDodgeAbility_Implementation()
{
	CallFightAbility(TEXT("Player.Ability.Dodge"));
}

void UFightComponent::CallSprintAbility_Implementation()
{
	CallFightAbility(TEXT("Player.Ability.Sprint"));
}
