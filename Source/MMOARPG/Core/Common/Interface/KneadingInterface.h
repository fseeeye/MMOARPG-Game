// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

// Plugins
#include "MMOARPGCommType.h"

#include "KneadingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UKneadingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MMOARPG_API IKneadingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IKneadingInterface();

	virtual void UpdateKneadingModelAttributes() = 0;
	virtual void UpdateKneadingModelAttributes(const FMMOARPGCharacterAppearance& InCA) = 0;

	// 这些函数可在蓝图或关卡蓝图图表中执行。
	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE void SetLegSize(float InSize) { LegSize = InSize; }
	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE void SetWaistSize(float InSize) { WaistSize = InSize; }
	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE void SetArmSize(float InSize) { ArmSize = InSize; }

	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE float GetLegSize() { return LegSize; }
	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE float GetWaistSize() { return WaistSize; }
	UFUNCTION(BlueprintCallable, Category = "Kneading")
	virtual FORCEINLINE float GetArmSize() { return ArmSize; }

	void ResetMeshPosition(USceneComponent* InMesh);

	FORCEINLINE void InitKneadingLocation(const FVector& InLocation) { Location = InLocation; }

protected:
	float LegSize;
	float WaistSize;
	float ArmSize;

	FVector Location;
};
