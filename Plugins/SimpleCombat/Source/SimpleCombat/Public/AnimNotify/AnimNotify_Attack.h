// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attack.generated.h"

class AAbilityHitCollision;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack"))
class SIMPLECOMBAT_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Attack();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
#if WITH_EDITORONLY_DATA
	virtual FLinearColor GetEditorColor() override { return FLinearColor::Red; }
#endif

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	TSubclassOf<AAbilityHitCollision> HitObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FVector HitObjectRelativeOffset; // Hit Object relative location offset

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	float HitObjectLifeSpan; // Hit Object life span

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bBindSocket; // if bind Hit Object at socket

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FName HitObjectBindSocketName; // socket name where Hit Object bind at

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bSingleTarget; // if Hit Object only affect single target

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitBox", meta = (EditCondition = "bBox"))
	FVector BoxExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitSphere", meta = (EditCondition = "bSphere"))
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitCapsule", meta = (EditCondition = "bCapsule"))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitCapsule", meta = (EditCondition = "bCapsule"))
	float CapsuleRadius;

public:
	UPROPERTY()
	bool bBox;

	UPROPERTY()
	bool bSphere;

	UPROPERTY()
	bool bCustom;

	UPROPERTY()
	bool bCapsule;
};
