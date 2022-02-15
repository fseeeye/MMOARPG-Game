// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../../Common/Interface/KneadingInterface.h"

#include "RoleHallCharacterStage.generated.h"

UCLASS()
class MMOARPG_API ARoleHallCharacterStage : public ACharacter, public IKneadingInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoleHallCharacterStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnCapsuleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	virtual void UpdateKneadingModelAttributes() override;
	virtual void UpdateKneadingModelAttributes(const FMMOARPGCharacterAppearance& InCA) override;

	FORCEINLINE void SetSlotPos(const int32 InSlotPos) { SlotPos = InSlotPos; }
	FORCEINLINE int32 GetSlotPos() const { return SlotPos; }

private:
	int32 SlotPos;
};
