// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../../../DataTable/CharacterAnimTableRow.h"

#include "MMOARPGCharacterBase.generated.h"

UCLASS()
class MMOARPG_API AMMOARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMMOARPGCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE bool IsFight() { return bFight; }
	FORCEINLINE FCharacterAnimTableRow* GetCharacterSwitchStateAnimTableRow() { return SwitchStateAnimTableRow; }

protected:
	UPROPERTY()
	bool bFight;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	int32 SwitchStateAnimTableID;
	
protected:
	FCharacterAnimTableRow* SwitchStateAnimTableRow;
};
