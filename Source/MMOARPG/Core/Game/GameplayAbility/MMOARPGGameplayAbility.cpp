#include "MMOARPGGameplayAbility.h"

#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>


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

UAbilityTask_PlayMontageAndWait* UMMOARPGGameplayAbility::CreatePlayMontageAndWaitProxy(
	FName TaskInstanceName, 
	UAnimMontage* InMontageToPlay,
	float Rate /*= 1.f*/, 
	FName StartSection /*= NAME_None*/, 
	bool bStopWhenAbilityEnds /*= true*/, 
	float AnimRootMotionTranslationScale /*= 1.f*/, 
	float StartTimeSeconds /*= 0.f*/)
{
	if (UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TaskInstanceName, InMontageToPlay, Rate, StartSection, bStopWhenAbilityEnds, AnimRootMotionTranslationScale, StartTimeSeconds))
	{
		// Bind task delegates
		AbilityTask_PlayMontageAndWait->OnCompleted.AddDynamic(this, &UMMOARPGGameplayAbility::OnCompleted);
		AbilityTask_PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UMMOARPGGameplayAbility::OnBlendOut);
		AbilityTask_PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UMMOARPGGameplayAbility::OnInterrupted);
		AbilityTask_PlayMontageAndWait->OnCancelled.AddDynamic(this, &UMMOARPGGameplayAbility::OnCancelled);

		AbilityTask_PlayMontageAndWait->Activate();

		return AbilityTask_PlayMontageAndWait;
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
