// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "../../DataTable/CharacterAnimTableRow.h"
#include "../../DataTable/CharacterStyleTableRow.h"

#include "MMOARPGGameState.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API AMMOARPGGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMMOARPGGameState();

public:
	FCharacterAnimTableRow* GetCharacterAnimTableRow(int32 InCharacterID);
	TArray<FCharacterAnimTableRow*>* GetCharacterAnimTableRows();

	FCharacterStyleTableRow* GetCharacterStyleTableRow(int32 InCharacterID);
	TArray<FCharacterStyleTableRow*>* GetCharacterStyleTableRows();

protected:
	template<class T>
	TArray<T*>* GetTableRows(UDataTable* InTablePtr, TArray<T*>& OutTableRows, const FString& InContextStr = TEXT("Default Table Context Message"))
	{
		if (!OutTableRows.Num() && InTablePtr)
		{
			// Read Anim Table into cache
			InTablePtr->GetAllRows(InContextStr, OutTableRows);
		}

		return &OutTableRows;
	}

	template<class T>
	T* GetTableRow(int32 InCharacterID, UDataTable* InTablePtr, TArray<T*> OutTableRows, const FString& InContextStr = TEXT("Default Table Context Message"))
	{
		if (TArray<T*>* TableRows = GetTableRows<T>(InTablePtr, OutTableRows, InContextStr))
		{
			if (TableRows->Num())
			{
				if (auto TargetTableRow = TableRows->FindByPredicate([&](T* InTR) { return InTR->CharacterID == InCharacterID; }))
				{
					return *TargetTableRow;
				}
			}
		}

		return nullptr;
	}

	/* Character Anim DataTable */
protected:
	UPROPERTY()
	UDataTable* CharacterAnimTablePtr;

	TArray<FCharacterAnimTableRow*> CharacterAnimTableRows; // Table Cache

	/* Character Style DataTable */
protected:
	UPROPERTY()
	UDataTable* CharacterStyleTablePtr;

	TArray<FCharacterStyleTableRow*> CharacterStyleTableRows; // Table Cache
};
