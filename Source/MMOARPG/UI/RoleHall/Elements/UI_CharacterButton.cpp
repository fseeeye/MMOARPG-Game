// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include <Kismet/GameplayStatics.h>

#include "../../../Core/RoleHall/RoleHallPawn.h"
#include "../../../Core/RoleHall/RoleHallPlayerState.h"
#include "UI_CharacterSelectionList.h"
#include "../UI_RoleHallMain.h"


void UUI_CharacterButton::NativeConstruct()
{
	Super::NativeConstruct();

	SlotPosition = INDEX_NONE;

	CharacterButton->OnReleased.AddDynamic(this, &UUI_CharacterButton::ClickedCharacterButton);

	// Set Widgets default Visibility
	CreationIcon->SetVisibility(ESlateVisibility::Visible);
	CharacterInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void UUI_CharacterButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterButton::InitWithCA(const FMMOARPGCharacterAppearance& InCA)
{
	if (InCA.SlotPos != INDEX_NONE)
	{
		// Set Character Appearance Widget Visible
		CreationIcon->SetVisibility(ESlateVisibility::Collapsed);
		CharacterInfo->SetVisibility(ESlateVisibility::Visible);

		// Set Character Appearance info to Widgets
		CharacterName->SetText(FText::FromString(InCA.Name));
		CreationDate->SetText(FText::FromString(InCA.CreationDate));
	}
}

void UUI_CharacterButton::ClickedCharacterButton()
{
	if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
	{
		if (auto UI_CharacterSelectionList = GetWidgetParent<UUI_CharacterSelectionList>())
		{
			// if this button slot is an empty button, get into Knead Face UI
			if (!RoleHallPlayerState->IsCharacterExistInSlot(SlotPosition))
			{
				// Step1: Generate Character

				// Step2: Switch Selection List to show Knead Face Widget
				UI_CharacterSelectionList->CreateKneadFacePanel();

				// Step3: Play NameBox ShowUp animation.
				if (auto UI_RoleHallMain = UI_CharacterSelectionList->GetWidgetParent<UUI_RoleHallMain>())
				{
					UI_RoleHallMain->PlayNameBoxShowUpAnim();
				}
			}
			else // or, get into the Game Level
			{
				// TODO: connect to DS Server

				// switch to Game Level
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameMap"));
			}

			UI_CharacterSelectionList->SetCurrentSlotPos(SlotPosition);
		}
	}
}
