// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGHUD.h"

AMMOARPGHUD::AMMOARPGHUD()
{
	// Load UI_GameMain_BP as Class
	static ConstructorHelpers::FClassFinder<UUI_GameMain> UI_GameMain_BP_ClassFinder(TEXT("/Game/UI/Game/UI_GameMain_BP"));
	GameMain_BP_Class = UI_GameMain_BP_ClassFinder.Class;
}

void AMMOARPGHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameMain_BP_Class)
	{
		// Create GameMain BP Widget in Game World.
		m_GameMain = CreateWidget<UUI_GameMain>(GetWorld(), GameMain_BP_Class);
		// Add GameMain UI widget to Viewport/PlayerScreen
		m_GameMain->AddToViewport();
	}
}
