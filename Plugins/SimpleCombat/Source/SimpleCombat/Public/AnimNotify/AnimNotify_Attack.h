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

#if WITH_EDITORONLY_DATA
	virtual FLinearColor GetEditorColor() override { return FLinearColor::Red; }
#endif

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	TSubclassOf<AAbilityHitCollision> HitObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	FVector HitObjectRelativelocation; // Hit Object relative location

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	float HitObjectLifeSpan; // Hit Object life span

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	bool bBindSocket; // if bind Hit Object at socket

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	FName HitObjectBindSocketName; // socket name where Hit Object bind at

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimAttack")
	bool bSingleTarget; // if Hit Object only affect single target
};
