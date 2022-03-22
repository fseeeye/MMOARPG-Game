#include "AbilityTask_PMAWDamage.h"

UAbilityTask_PMAWDamage::UAbilityTask_PMAWDamage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UAbilityTask_PMAWDamage::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	if (AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
		}
	}

	Super::Activate();
}

void UAbilityTask_PMAWDamage::OnDestroy(bool AbilityEnded)
{
	Super::OnDestroy(AbilityEnded);

}
