// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMOARPGCharacter.h"

#include "../../Common/Interface/KneadingInterface.h"

#include "MMOARPGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API AMMOARPGPlayerCharacter : public AMMOARPGCharacter, public IKneadingInterface
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Kneading Data */
protected:
	UFUNCTION(Server, Reliable)
	void UpdateKneadingDataOnServer(int32 InUserID);

public:
	UFUNCTION(Client, Reliable)
	void UpdateKneadingDataOnClient(const FMMOARPGCharacterAppearance& InCA);

public:
	virtual void UpdateKneadingModelAttributes() override;
	virtual void UpdateKneadingModelAttributes(const FMMOARPGCharacterAppearance& InCA) override;
};
