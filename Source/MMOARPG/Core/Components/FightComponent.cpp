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

		if (GetWorld())
		{
			if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
			{
				if (FCharacterAbilityTableRow* AbilityTR = GameState->GetCharacterAbilityTableRow(Owner_CharacterBase->GetCharacterID()))
				{
					// Add inherent abilities
					CharacterAbilities.Add(TEXT("NormalAttack"), AddAbility(AbilityTR->NormalAttack));
					// Register ComboAttack
					RegisterComboAttack(ComboAttack, TEXT("NormalAttack")); // register normal attack ability to combo attack
				}
			}

			// Init GAS info
			Owner_GASComponent->InitAbilityActorInfo(Owner_CharacterBase.Get(), Owner_CharacterBase.Get());
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

void UFightComponent::NormalAttack(const FName& InAbilityName)
{
	if (Owner_GASComponent.IsValid())
	{
		if (FGameplayAbilitySpecHandle* NormalAttackHandle = CharacterAbilities.Find(TEXT("NormalAttack"))) // TODO
		{
			Owner_GASComponent->TryActivateAbility(*NormalAttackHandle);
		}
	}
}

void UFightComponent::RegisterComboAttack(FSimpleComboAttack& InComboAttack, const FName& InAbilityName)
{
	InComboAttack.OutCharacter = Owner_CharacterBase.Get();
	InComboAttack.ComboAbilityName = InAbilityName;
	if (UMMOARPGGameplayAbility* GameplayAbility = FindAbility(InAbilityName))
	{
		InComboAttack.MaxIndex = GameplayAbility->GetMontageCompositeSectionsNum();
	}
	//else
	//{
	//	InComboAttack.MaxIndex = 4;
	//}
}
