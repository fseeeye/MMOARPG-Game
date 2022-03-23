#include "MMOARPGGameplayAbility.h"

#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include <AbilitySystemComponent.h>

#include "Tasks/AbilityTask_PMAWDamage.h"


UMMOARPGGameplayAbility::UMMOARPGGameplayAbility()
{

}

void UMMOARPGGameplayAbility::OnCompleted()
{
	K2_OnCompleted();
}

void UMMOARPGGameplayAbility::OnBlendOut()
{
	K2_OnBlendOut();
}

void UMMOARPGGameplayAbility::OnInterrupted()
{
	K2_OnInterrupted();
}

void UMMOARPGGameplayAbility::OnCancelled()
{
	K2_OnCancelled();
}

void UMMOARPGGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData InPayload)
{
	// Damage Main logic
	if (FMMOARPGGameplayEffects* AbilityEffects = EffectMap.Find(InGameplayTag))
	{
		FMMOARPGGameplayEffectSpec EffectSpec;

		// Get TargetDataHandle
		FGameplayAbilityTargetData_ActorArray* NewTargetData_ActorArray = new FGameplayAbilityTargetData_ActorArray();
		NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*>(InPayload.Target)); // get target actor data
		EffectSpec.TargetDataHandle.Add(NewTargetData_ActorArray);

		// Get EffectSpecHandles from AbilityEffect Container
		for (auto& AbilityEffectClass : AbilityEffects->TargetEffectClasses)
		{
			FGameplayEffectSpecHandle NewEffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(AbilityEffectClass, 1, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo)); // TODO: level

			if (NewEffectSpecHandle.IsValid())
			{
				FGameplayAbilitySpec* AbilitySpec = GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);

				if (AbilitySpec)
				{
					ApplyAbilityTagsToGameplayEffectSpec(*NewEffectSpecHandle.Data.Get(), AbilitySpec);
					NewEffectSpecHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;

					EffectSpec.EffectSpecHandles.Add(NewEffectSpecHandle);
				}
			}
		}

		// Apply effects
		for (auto& EffectSpecHandle : EffectSpec.EffectSpecHandles)
		{
			TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(EffectSpecHandle, EffectSpec.TargetDataHandle);
		}
	}
}

UAbilityTask_PlayMontageAndWait* UMMOARPGGameplayAbility::CreatePlayMontageAndWaitProxy(
	FName TaskInstanceName, 
	UAnimMontage* InMontageToPlay,
	float Rate /*= 1.f*/, 
	FName StartSection /*= NAME_None*/, 
	bool bStopWhenAbilityEnds /*= true*/, 
	float AnimRootMotionTranslationScale /*= 1.f*/, 
	float StartTimeSeconds /*= 0.f*/)
{
	if (UAbilityTask_PMAWDamage* AbilityTask_PMAWDamage = UAbilityTask_PMAWDamage::CreatePMAWDamageProxy(this, TaskInstanceName, InMontageToPlay, AbilityTags, Rate, StartSection, bStopWhenAbilityEnds, AnimRootMotionTranslationScale, StartTimeSeconds))
	{
		// Bind task delegates
		AbilityTask_PMAWDamage->OnCompleted.AddDynamic(this, &UMMOARPGGameplayAbility::OnCompleted);
		AbilityTask_PMAWDamage->OnBlendOut.AddDynamic(this, &UMMOARPGGameplayAbility::OnBlendOut);
		AbilityTask_PMAWDamage->OnInterrupted.AddDynamic(this, &UMMOARPGGameplayAbility::OnInterrupted);
		AbilityTask_PMAWDamage->OnCancelled.AddDynamic(this, &UMMOARPGGameplayAbility::OnCancelled);
		AbilityTask_PMAWDamage->OnDamageEventReceived.AddDynamic(this, &UMMOARPGGameplayAbility::OnDamageGameplayEvent);

		AbilityTask_PMAWDamage->Activate();

		return AbilityTask_PMAWDamage;
	}

	return nullptr;
}

UAbilityTask_PlayMontageAndWait* UMMOARPGGameplayAbility::PlayMontageAndWaitSimple(FName StartSection /*= NAME_None*/)
{
	return CreatePlayMontageAndWaitProxy(NAME_None, MontageToPlay, 1.f, StartSection);
}

int32 UMMOARPGGameplayAbility::GetMontageCompositeSectionsNum()
{
	if (MontageToPlay)
	{
		return MontageToPlay->CompositeSections.Num();
	}

	return 0;
}
