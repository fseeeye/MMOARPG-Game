// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOARPGGameMode.h"
#include "MMOARPGCharacter.h"
#include "MMOARPGHUD.h"

#include "UObject/ConstructorHelpers.h"

AMMOARPGGameMode::AMMOARPGGameMode()
{
	// Register HUD
	HUDClass = AMMOARPGHUD::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
