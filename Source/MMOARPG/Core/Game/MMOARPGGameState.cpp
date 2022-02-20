// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGGameState.h"

#include <Engine/DataTable.h>

AMMOARPGGameState::AMMOARPGGameState()
{
	// Get Character Animation Table BP
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimTable(TEXT("/Game/DataTable/DT_CharacterAnimTable"));
	CharacterAnimTablePtr = CharacterAnimTable.Object;
}

FCharacterAnimTableRow* AMMOARPGGameState::GetCharacterAnimTableRow(int32 InAnimTableID)
{
	if (TArray<FCharacterAnimTableRow*>* AnimTableRows = GetCharacterAnimTableRows())
	{
		if (AnimTableRows->Num())
		{
			if (auto TargetTableRow = AnimTableRows->FindByPredicate([&](FCharacterAnimTableRow* InTR) { return InTR->ID == InAnimTableID; }))
			{
				return *TargetTableRow;
			}
		}
	}

	return nullptr;
}

TArray<FCharacterAnimTableRow*>* AMMOARPGGameState::GetCharacterAnimTableRows()
{
	if (!CharacterAnimTableRows.Num() && CharacterAnimTablePtr)
	{
		// Read Anim Table into cache
		CharacterAnimTablePtr->GetAllRows(TEXT("AnimTable"), CharacterAnimTableRows);
	}

	return &CharacterAnimTableRows;
}
