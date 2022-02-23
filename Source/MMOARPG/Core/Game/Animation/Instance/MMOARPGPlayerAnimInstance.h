// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMOARPGCharacterAnimInstance.h"
#include "MMOARPGPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UMMOARPGPlayerAnimInstance : public UMMOARPGCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	/*** KneadingFace ***/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	float LegSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	float WaistSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	float ArmSize;
};
