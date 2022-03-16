// Fill out your copyright notice in the Description page of Project Settings.


#include "FightComponent.h"

#include "../Game/MMOARPGGameState.h"


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
			// Add inherent abilities
			if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
			{
				if (FCharacterAbilityTableRow* AbilityTR = GameState->GetCharacterAbilityTableRow(Owner_CharacterBase->GetCharacterID()))
				{
					CharacterAbilities.Add(TEXT("NormalAttack"), AddAbility(AbilityTR->NormalAttack));
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

void UFightComponent::NormalAttack(const FName& InKey)
{
	if (Owner_GASComponent.IsValid())
	{
		if (FGameplayAbilitySpecHandle* NormalAttackHandle = CharacterAbilities.Find(TEXT("NormalAttack"))) // TODO
		{
			Owner_GASComponent->TryActivateAbility(*NormalAttackHandle);
		}
	}
}
