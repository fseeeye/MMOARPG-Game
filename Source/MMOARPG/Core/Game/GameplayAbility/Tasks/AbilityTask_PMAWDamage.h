#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilityTask_PMAWDamage.generated.h"

/** Ability task to simply play a montage and register Damage Gameplay Event */
UCLASS()
class MMOARPG_API UAbilityTask_PMAWDamage : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:
	UAbilityTask_PMAWDamage(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

public:
	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate DamageEventReceived;

private:
	FDelegateHandle DamageEventHandle;
};
