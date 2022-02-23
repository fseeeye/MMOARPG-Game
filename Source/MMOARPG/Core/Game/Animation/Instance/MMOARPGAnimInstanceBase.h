// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include <GameFramework/Character.h>

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

	virtual void InitAnimInstance(ACharacter* InCharacter);

	/*** Basis ***/
public:
	// whether current character is death.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	bool bDeath;

	// whether current character is in air.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	bool bInAir;

	// whether current character is in fight state.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	bool bFight;

	// the movement speed of current character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes")
	float Speed;

	/*** FootIK ***/
public:
	UPROPERTY(EditDefaultsOnly, Category = "AnimAttributes|FootIK")
	bool bFootIK;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes|FootIK")
	int32 FootIK_ID;

	UPROPERTY(EditDefaultsOnly, Category = "AnimAttributes|FootIK")
	TArray<FName> FootIK_BoneNames; // TODO: For many legs pawn

	UPROPERTY(EditDefaultsOnly, Category = "AnimAttributes|FootIK")
	FName FootIK_LeftBoneName;

	UPROPERTY(EditDefaultsOnly, Category = "AnimAttributes|FootIK")
	FName FootIK_RightBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes|FootIK")
	float FootIK_LeftOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes|FootIK")
	float FootIK_RightOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttributes|FootIK")
	float FootIK_CentroidOffsetZ;

public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetFootIKOffset(const FName& InBoneName);
};
