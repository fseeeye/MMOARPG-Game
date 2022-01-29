// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallPlayerState.h"

bool ARoleHallPlayerState::IsCharacterExistInSlot(const int32 InSlotPos)
{
	return GetCharacterAppearanceWithPos(InSlotPos) != nullptr;
}

FMMOARPGCharacterAppearance* ARoleHallPlayerState::GetRecentCharacterAppearance()
{
	FDateTime MaxDateTime;
	int32 MaxDateIndex = INDEX_NONE;
	for (int32 i = 0; i < CharacterAppearances.Num(); ++i)
	{
		FDateTime DateTime;
		FDateTime::Parse(CharacterAppearances[i].CreationDate, DateTime);
		if (DateTime > MaxDateTime)
		{
			MaxDateTime = DateTime;
			MaxDateIndex = i;
		}
	}

	if (MaxDateIndex == INDEX_NONE)
	{
		return nullptr;
	}
	return &CharacterAppearances[MaxDateIndex];
}

FMMOARPGCharacterAppearance* ARoleHallPlayerState::GetCharacterAppearanceWithPos(const int32 InSlotPos)
{
	return CharacterAppearances.FindByPredicate([InSlotPos](const FMMOARPGCharacterAppearance& InCA){ return InSlotPos == InCA.SlotPos; });
}

FMMOARPGCharacterAppearance* ARoleHallPlayerState::AddCharacterAppearance(const int32 InSlotPos)
{
	FMMOARPGCharacterAppearance* CAptr = nullptr;
	if (FMMOARPGCharacterAppearance* CA = GetCharacterAppearanceWithPos(InSlotPos))
	{
		CAptr = CA;
	}
	else
	{
		CharacterAppearances.Add(FMMOARPGCharacterAppearance());
		FMMOARPGCharacterAppearance& NewCA = CharacterAppearances.Last();
		NewCA.SlotPos = InSlotPos;
		
		CAptr = &NewCA;
	}

	return CAptr;
}

int32 ARoleHallPlayerState::AddCharacterAppearance(const FMMOARPGCharacterAppearance& InCA)
{
	return CharacterAppearances.Add(InCA);
}
