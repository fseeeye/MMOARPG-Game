// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "../../UI/RoleHall/UI_RoleHallMain.h"

#include "RoleHallHUD.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API ARoleHallHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	TSubclassOf<UUI_RoleHallMain> RoleHallMain_BP_Class;
public:
	ARoleHallHUD();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UUI_RoleHallMain* m_RoleHallMain;
};
