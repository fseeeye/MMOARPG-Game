// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterSelectionList.h"
#include "Components/ScrollBoxSlot.h"

void UUI_CharacterSelectionList::NativeConstruct()
{
	Super::NativeConstruct();

	InitCharacterButtons(3);
}

void UUI_CharacterSelectionList::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterSelectionList::InitCharacterButtons(const int32 InNumber)
{
	// Create Buttons dynamically
	if (UI_CharacterButtonClass)
	{
		for (int32 i = 0; i < InNumber; ++i)
		{
			if (auto CharacterButton = CreateWidget<UUI_CharacterButton>(GetWorld(), UI_CharacterButtonClass))
			{
				CharacterButton->SetWidgetParent(this);
				// Switch Button's parent from World to CharacterList
				if (UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(CharacterButton)))
				{
					// Set slot padding
					ScrollBoxSlot->SetPadding(10.f);
				}
			}
		}
	}
}
