// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGGameState.h"

#include <Engine/DataTable.h>

AMMOARPGGameState::AMMOARPGGameState()
{
	// Get Character Animation Table BP
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimTable(TEXT("/Game/DataTable/DT_CharacterAnimTable"));
	CharacterAnimTablePtr = CharacterAnimTable.Object;

	// Get Character Style Table BP
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStyleTable(TEXT("/Game/DataTable/DT_CharacterStyleTable"));
	CharacterStyleTablePtr = CharacterStyleTable.Object;

	// Get Character Ability Table BP
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAbilityTable(TEXT("/Game/DataTable/DT_CharacterAbilityTable"));
	CharacterAbilityTablePtr = CharacterAbilityTable.Object;
}

FCharacterAnimTableRow* AMMOARPGGameState::GetCharacterAnimTableRow(int32 InCharacterID)
{
	return GetTableRow(InCharacterID, CharacterAnimTablePtr, CharacterAnimTableRows, TEXT("Character Animation Table"));
}

TArray<FCharacterAnimTableRow*>* AMMOARPGGameState::GetCharacterAnimTableRows()
{
	return GetTableRows(CharacterAnimTablePtr, CharacterAnimTableRows, TEXT("Character Animation Table"));
}

FCharacterStyleTableRow* AMMOARPGGameState::GetCharacterStyleTableRow(int32 InCharacterID)
{
	return GetTableRow(InCharacterID, CharacterStyleTablePtr, CharacterStyleTableRows, TEXT("Character Style Table"));
}

TArray<FCharacterStyleTableRow*>* AMMOARPGGameState::GetCharacterStyleTableRows()
{
	return GetTableRows(CharacterStyleTablePtr, CharacterStyleTableRows, TEXT("Character Style Table"));
}

FCharacterAbilityTableRow* AMMOARPGGameState::GetCharacterAbilityTableRow(int32 InCharacterID)
{
	return GetTableRow(InCharacterID, CharacterAbilityTablePtr, CharacterAbilityTableRows, TEXT("Character Ability Table"));
}

TArray<FCharacterAbilityTableRow*>* AMMOARPGGameState::GetCharacterAbilityTableRows()
{
	return GetTableRows(CharacterAbilityTablePtr, CharacterAbilityTableRows, TEXT("Character Ability Table"));
}
