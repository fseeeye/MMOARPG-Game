// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "../../UI/Game/UI_GameMain.h"

#include "MMOARPGHUD.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API AMMOARPGHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UUI_GameMain> GameMain_BP_Class;

public:
	AMMOARPGHUD();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UUI_GameMain* m_GameMain;
};
