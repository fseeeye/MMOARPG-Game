// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../../../DataTable/CharacterAnimTableRow.h"
#include "../MMOARPGGameMode.h"

#include "MMOARPGCharacterBase.generated.h"

UCLASS()
class MMOARPG_API AMMOARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

	friend class AMMOARPGGameMode;

public:
	// Sets default values for this character's properties
	AMMOARPGCharacterBase();

	// For Replicated property
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	FORCEINLINE int32 GetSwitchStateAnimTableID() { return SwitchStateAnimTableID; }
	FORCEINLINE FCharacterAnimTableRow* GetCharacterSwitchStateAnimTableRow() { return SwitchStateAnimTableRow; }

protected:
	// Do when `bFight` changed
	UFUNCTION()
	virtual void OnRep_FightChanged() {}

	// RPC Call Server to change `bFight` property
	UFUNCTION(Server, Reliable)
	void ChangeFightOnServer(bool bNewFight);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_FightChanged)
	bool bFight;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	int32 SwitchStateAnimTableID;
	
protected:
	FCharacterAnimTableRow* SwitchStateAnimTableRow;
};
