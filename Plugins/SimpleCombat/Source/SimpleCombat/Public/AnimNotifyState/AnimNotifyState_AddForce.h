// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AddForce.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS()
class SIMPLECOMBAT_API UAnimNotifyState_AddForce : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_AddForce();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

private:
	FVector CalcForceDirectionInCharacterSpace(ACharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AddForce")
	FVector ForceDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AddForce")
	float ForceSize;

private:
	float TotalDurationTime;
	float ForceConsuming;
};
