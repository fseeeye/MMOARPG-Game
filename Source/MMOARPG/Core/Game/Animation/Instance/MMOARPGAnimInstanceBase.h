// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MMOARPGAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UMMOARPGAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMMOARPGAnimInstanceBase();

	virtual void NativeInitializeAnimation() override; // like BeginPlay
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // like Tick

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	bool bDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	bool bInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	float Speed;
};
