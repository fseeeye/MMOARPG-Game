// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "MMOARPGCommType.h" // Plugin: MMOARPGComm

#include "RoleHallPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API ARoleHallPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	inline FMMOARPGCharacterAppearances& GetCharacterAppearances() { return CharacterAppearances; }

	bool IsCharacterExistInSlot(const int32 InSlotPos);

	FMMOARPGCharacterAppearance* GetRecentCharacter();
	
private:
	FMMOARPGCharacterAppearances CharacterAppearances;
};
