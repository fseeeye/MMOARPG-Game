// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Instance/MMOARPGAnimInstanceBase.h"
#include "ComponentAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UComponentAnimInstanceBase : public UMMOARPGAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override; // like BeginPlay
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // like Tick

public:
	void UpdateAxisSpeed3D(float InMaxSpeed);
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	FVector AxisSpeed3D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	FVector2D RotationRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	bool bFast;
};
