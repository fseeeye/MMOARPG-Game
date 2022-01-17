// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginHUD.h"

ALoginHUD::ALoginHUD()
{
	// Load UI_LoginMain_BP from spec path as Class
	static ConstructorHelpers::FClassFinder<UUI_LoginMain> UI_LoginMain_BP_ClassFinder(TEXT("/Game/UI/Login/UI_LoginMain_BP"));
	LoginMain_BP_Class = UI_LoginMain_BP_ClassFinder.Class;
}

void ALoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LoginMain_BP_Class)
	{
		// Create LoginMain BP Widget in Game World
		m_LoginMain = CreateWidget<UUI_LoginMain>(GetWorld(), LoginMain_BP_Class);
		// Add LoginMain BP Widget to Viewport/PlayerScreen
		m_LoginMain->AddToViewport();
	}
}
