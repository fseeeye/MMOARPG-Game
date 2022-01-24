// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterSelectionList.h"

#include "Components/ScrollBoxSlot.h"
#include "UI_KneadFace.h"
#include "../../../Core/RoleHall/RoleHallPlayerState.h"


void UUI_CharacterSelectionList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_CharacterSelectionList::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterSelectionList::CreateKneadFacePanel()
{
	// Clean List
	List->ClearChildren();

	// Creat Knead Face Panel
	if (UI_KneadFaceSubClass)
	{
		if (auto KneadFacePanel = CreateWidget<UUI_KneadFace>(GetWorld(), UI_KneadFaceSubClass))
		{
			// Switch Button's parent from World to CharacterList
			KneadFacePanel->SetWidgetParent(this);

			if (auto ScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(KneadFacePanel)))
			{
				// Set slot padding
				ScrollBoxSlot->SetPadding(10.f);
				// TODO
			}
		}
	}
}

void UUI_CharacterSelectionList::CreateCharacterButtons()
{
	// get character appearances in player state & init buttons
	if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
	{
		InitCharacterButtons(RoleHallPlayerState->GetCharacterAppearances());
	}
}

void UUI_CharacterSelectionList::InitCharacterButtons(FMMOARPGCharacterAppearances& InCAs)
{
	// Clean List
	List->ClearChildren();

	// Create Buttons dynamically
	if (UI_CharacterButtonSubClass)
	{
		for (int32 i = 0; i < 3; ++i)
		{
			if (auto CharacterButton = CreateWidget<UUI_CharacterButton>(GetWorld(), UI_CharacterButtonSubClass))
			{
				CharacterButton->SetSlotPosition(i);
				// Switch Button's parent from World to CharacterList
				CharacterButton->SetWidgetParent(this);

				if (UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(CharacterButton)))
				{
					// Set slot padding
					ScrollBoxSlot->SetPadding(10.f);
				}

				if (const FMMOARPGCharacterAppearance* CharacterAppearance =
					InCAs.FindByPredicate([&](const FMMOARPGCharacterAppearance& InCharacterAppearance)
					{
						return InCharacterAppearance.SlotPos == i;
					}))
				{
					CharacterButton->InitWithCA(*CharacterAppearance);
				}
			}
		}
	}
}
