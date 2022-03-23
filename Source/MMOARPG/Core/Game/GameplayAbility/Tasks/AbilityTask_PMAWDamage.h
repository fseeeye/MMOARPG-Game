#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilityTask_PMAWDamage.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMontageWaitForDamageEventSimpleDelegate, FGameplayTag, InGameplayTag, FGameplayEventData, InPayload);

/** Ability task to simply play a montage and register Damage Gameplay Event */
UCLASS()
class MMOARPG_API UAbilityTask_PMAWDamage : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:
	UAbilityTask_PMAWDamage(const FObjectInitializer& ObjectInitializer);

public:
	static UAbilityTask_PMAWDamage* CreatePMAWDamageProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer InEventTagContainer, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.f, float StartTimeSeconds = 0.f);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

private:
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* InPayload);

public:
	UPROPERTY(BlueprintAssignable)
	FMontageWaitForDamageEventSimpleDelegate OnDamageEventReceived;

private:
	FDelegateHandle DamageEventHandle;

	UPROPERTY()
	FGameplayTagContainer EventTagContainer;
};
