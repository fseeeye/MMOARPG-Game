#include "AbilityTask_PMAWDamage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UAbilityTask_PMAWDamage::UAbilityTask_PMAWDamage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UAbilityTask_PMAWDamage* UAbilityTask_PMAWDamage::CreatePMAWDamageProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer InEventTagContainer, float Rate /*= 1.f*/, FName StartSection /*= NAME_None*/, bool bStopWhenAbilityEnds /*= true*/, float AnimRootMotionTranslationScale /*= 1.f*/, float StartTimeSeconds /*= 0.f*/)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UAbilityTask_PMAWDamage* MyObj = NewAbilityTask<UAbilityTask_PMAWDamage>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->StartTimeSeconds = StartTimeSeconds;

	MyObj->EventTagContainer = InEventTagContainer; // added

	return MyObj;
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
			// register delegate
			DamageEventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				EventTagContainer,
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UAbilityTask_PMAWDamage::OnDamageGameplayEvent)
			);
		}
	}

	Super::Activate();
}

void UAbilityTask_PMAWDamage::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent)
	{
		// remove delegate
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTagContainer, DamageEventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_PMAWDamage::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* InPayload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// Post Gameplay Event
		FGameplayEventData Payload = *InPayload;
		Payload.EventTag = InGameplayTag;

		OnDamageEventReceived.Broadcast(InGameplayTag, Payload);
	}
}
