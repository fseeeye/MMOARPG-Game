// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "../../DataTable/CharacterAnimTableRow.h"

#include "MMOARPGGameState.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API AMMOARPGGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AMMOARPGGameState();

	FCharacterAnimTableRow* GetCharacterAnimTableRow(int32 InAnimTableID);
	TArray<FCharacterAnimTableRow*>* GetCharacterAnimTableRows();

private:
	UPROPERTY()
	UDataTable* CharacterAnimTablePtr;

	TArray<FCharacterAnimTableRow*> CharacterAnimTableRows; // Table Cache
};
