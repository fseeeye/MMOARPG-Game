// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginHUD.h"

#include "../../UI/Login/UI_LoginMain.h"

ALoginHUD::ALoginHUD()
{
	// Load UI_LoginMain_BP from spec path as Class
	static ConstructorHelpers::FClassFinder<UUI_LoginMain> UI_LoginMain_BP_ClassFinder(TEXT("/Game/UI/Login/UI_LoginMain_BP"));
	UI_LoginMain_BP_Class = UI_LoginMain_BP_ClassFinder.Class;
}

void ALoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UI_LoginMain_BP_Class)
	{
		// Create LoginMain UI widget from UI_LoginMain_BP
		m_UI_LoginMain_BP = CreateWidget<UUI_LoginMain>(GetWorld(), UI_LoginMain_BP_Class);
		// Add LoginMain UI widget to Viewport/PlayerScreen
		m_UI_LoginMain_BP->AddToViewport();
	}
}
