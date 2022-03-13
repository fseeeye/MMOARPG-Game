// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentAnimInstanceBase.h"
#include "MMOARPGSwimAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UMMOARPGSwimAnimInstance : public UComponentAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override; // like BeginPlay
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // like Tick
};
