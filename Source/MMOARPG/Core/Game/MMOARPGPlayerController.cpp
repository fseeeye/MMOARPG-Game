// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerController.h"

#include "MMOARPGGameState.h"
#include "MMOARPGPlayerState.h"
#include "Character/MMOARPGCharacter.h"
#include "Character/MMOARPGPlayerCharacter.h"

AMMOARPGPlayerController::AMMOARPGPlayerController()
{
	bShowMouseCursor = true;
}

void AMMOARPGPlayerController::ReplaceCharacter_Implementation(int32 InCharacterID)
{
	if (AMMOARPGCharacterBase* OldCharacter = GetPawn<AMMOARPGCharacterBase>())
	{
		if (OldCharacter->GetCharacterID() == InCharacterID)
			return;

		// Step1: Get Character Style Table
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			if (FCharacterStyleTableRow* StyleTableRow = GameState->GetCharacterStyleTableRow(InCharacterID))
			{
				// Step2: Spawn Character in current location & rotation
				if (AMMOARPGCharacter* NewCharacter = GetWorld()->SpawnActor<AMMOARPGCharacter>(
						StyleTableRow->CharacterClass,
						OldCharacter->GetActorLocation(),
						OldCharacter->GetActorRotation()
					))
				{
					if (AMMOARPGPlayerState* MMOARPGPlayerState = GetPlayerState<AMMOARPGPlayerState>())
					{
						// if Character is Player Character, impl CA
						if (AMMOARPGPlayerCharacter* NewPlayerCharacter = Cast<AMMOARPGPlayerCharacter>(NewCharacter))
						{
							NewPlayerCharacter->UpdateKneadingModelAttributes(MMOARPGPlayerState->GetCA()); // Update CA on Server
							NewPlayerCharacter->UpdateKneadingDataOnClient(MMOARPGPlayerState->GetCA());    // Update CA on primary Client (RPC)
						}

						// Step3: Replace Character & Destroy old Character
						OnPossess(NewCharacter);
						OldCharacter->Destroy(true);
					}
				}
			}
		}
	}
}
