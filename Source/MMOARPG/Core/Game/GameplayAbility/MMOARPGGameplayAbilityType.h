#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MMOARPGGameplayAbilityType.generated.h"

USTRUCT(BlueprintType)
struct FMMOARPGGameplayEffects
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> TargetEffectClasses;
};

USTRUCT(BlueprintType)
struct FMMOARPGGameplayEffectSpec
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	TArray<FGameplayEffectSpecHandle> EffectSpecHandles;
};

