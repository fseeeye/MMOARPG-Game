// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Instance/MMOARPGAnimInstanceBase.h"
#include "MMOARPGFlyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UMMOARPGFlyAnimInstance : public UMMOARPGAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void InitAnimInstance(ACharacter* InCharacter) override;

	virtual void NativeInitializeAnimation() override; // like BeginPlay
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // like Tick
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	FVector FlySpeed;
};
