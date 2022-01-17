// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallHUD.h"

ARoleHallHUD::ARoleHallHUD()
{
	// Load UI_RoleHall_BP as Class
	static ConstructorHelpers::FClassFinder<UUI_RoleHallMain> UI_RoleHallMain_BP_ClassFinder(TEXT("/Game/UI/RoleHall/UI_RoleHallMain_BP"));
	RoleHallMain_BP_Class = UI_RoleHallMain_BP_ClassFinder.Class;
}

void ARoleHallHUD::BeginPlay()
{
	Super::BeginPlay();

	if (RoleHallMain_BP_Class)
	{
		// Create RoleHallMain BP Widget in Game World.
		m_RoleHallMain = CreateWidget<UUI_RoleHallMain>(GetWorld(), RoleHallMain_BP_Class);
		// Add LoginMain UI widget to Viewport/PlayerScreen
		m_RoleHallMain->AddToViewport();
	}
}

