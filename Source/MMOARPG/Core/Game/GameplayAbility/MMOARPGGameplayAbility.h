#pragma once

#include <Abilities/GameplayAbility.h>

#include "MMOARPGGameplayAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;

UCLASS()
class MMOARPG_API UMMOARPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UMMOARPGGameplayAbility();

	/* Play Montage */
public:
	UFUNCTION()
	virtual void OnCompleted();

	UFUNCTION()
	virtual void OnBlendOut();

	UFUNCTION()
	virtual void OnInterrupted();

	UFUNCTION()
	virtual void OnCancelled();

	UFUNCTION(BlueprintImplementableEvent, Category = "UMMOARPGGameplayAbility|MontageAbility", DisplayName = "OnCompleted", meta = (ScriptName = "OnCompleted"))
	void K2_OnCompleted();

	UFUNCTION(BlueprintImplementableEvent, Category = "UMMOARPGGameplayAbility|MontageAbility", DisplayName = "OnBlendOut", meta = (ScriptName = "OnBlendOut"))
	void K2_OnBlendOut();

	UFUNCTION(BlueprintImplementableEvent, Category = "UMMOARPGGameplayAbility|MontageAbility", DisplayName = "OnInterrupted", meta = (ScriptName = "OnInterrupted"))
	void K2_OnInterrupted();

	UFUNCTION(BlueprintImplementableEvent, Category = "UMMOARPGGameplayAbility|MontageAbility", DisplayName = "OnCancelled", meta = (ScriptName = "OnCancelled"))
	void K2_OnCancelled();

	// Call "AbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy"
	UFUNCTION(BlueprintCallable, Category = "UMMOARPGGameplayAbility|MontageAbility", meta = (DisplayName = "MMOARPG_PlayMontageAndWait"))
	UAbilityTask_PlayMontageAndWait* CreatePlayMontageAndWaitProxy(FName TaskInstanceName, UAnimMontage* InMontageToPlay, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.f, float StartTimeSeconds = 0.f);

	UFUNCTION(BlueprintCallable, Category = "UMMOARPGGameplayAbility|MontageAbility")
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWaitSimple(FName StartSection = NAME_None);

public:
	int32 GetMontageCompositeSectionsNum();

public:
	UPROPERTY(EditDefaultsOnly, Category = "UMMOARPGGameplayAbility|MontageAbility")
	UAnimMontage* MontageToPlay;
};
