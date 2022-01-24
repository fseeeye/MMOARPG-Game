// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "../../../Core/RoleHall/RoleHallPawn.h"
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
	// TODO
	if (1)
	{
		// Step1: Generate Character
		if (RoleHallCharacterStageClass)
		{
			// Get RoleHall Pawn
			if (ARoleHallPawn* RoleHallPawn = GetPawn<ARoleHallPawn>())
			{
				// if Character already exits, destroy it.
				if (RoleHallPawn->RoleHallCharacterStage)
				{
					RoleHallPawn->RoleHallCharacterStage->Destroy();
					RoleHallPawn->RoleHallCharacterStage = nullptr;
				}

				// Spawn Showing Character in World
				RoleHallPawn->RoleHallCharacterStage =
					GetWorld()->SpawnActor<ARoleHallCharacterStage>(RoleHallCharacterStageClass, RoleHallCharacterSpawnPoint, FRotator::ZeroRotator);

				if (RoleHallPawn->RoleHallCharacterStage)
				{

				}
			}
		}

		if (auto UI_CharacterSelectionList = GetWidgetParent<UUI_CharacterSelectionList>())
		{
			// Step2: Switch Selection List to show Knead Face Widget
			UI_CharacterSelectionList->CreateKneadFacePanel();

			// Step3: Play NameBox ShowUp animation.
			if (auto UI_RoleHallMain = UI_CharacterSelectionList->GetWidgetParent<UUI_RoleHallMain>())
			{
				UI_RoleHallMain->PlayNameBoxShowUpAnim();
			}
		}
	}
}
