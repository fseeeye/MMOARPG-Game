// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterSelectionList.h"

#include "Components/ScrollBoxSlot.h"
#include "UI_KneadFace.h"

#include "../../../Core/RoleHall/RoleHallPawn.h"
#include "../../../Core/RoleHall/RoleHallPlayerState.h"
#include "../../../Core/RoleHall/Character/RoleHallCharacterStage.h"
#include "../UI_RoleHallMain.h"


void UUI_CharacterSelectionList::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentSelectedSlotPos = 0;
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

void UUI_CharacterSelectionList::SpawnCharacterStage(const int32 InSlotPos)
{
	if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
	{
		SpawnCharacterStage(RoleHallPlayerState->GetCharacterAppearances().FindByPredicate([&](const FMMOARPGCharacterAppearance& InCA)
		{
			return InCA.SlotPos == InSlotPos;
		}));
	}
}

void UUI_CharacterSelectionList::SpawnCharacterStage()
{
	SpawnCharacterStage(CurrentSelectedSlotPos);
}

void UUI_CharacterSelectionList::SpawnCharacterStage(const FMMOARPGCharacterAppearance* InCA)
{
	if (InCA)
	{
		if (RoleHallCharacterStageClass)
		{
			if (ARoleHallCharacterStage* RoleHallCharacterStage = CreateCharacterStage())
			{
				RoleHallCharacterStage->SetSlotPos(InCA->SlotPos);
				RoleHallCharacterStage->UpdateKneadingModelAttributes(*InCA);
			}
		}
	}
}

ARoleHallCharacterStage* UUI_CharacterSelectionList::CreateCharacterStage()
{
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

			return RoleHallPawn->RoleHallCharacterStage;
		}
	}

	return nullptr;
}

void UUI_CharacterSelectionList::HighlightButton(int32 InSlotPos)
{
	FindByPredicateInList<UUI_CharacterButton>([InSlotPos](UUI_CharacterButton* InButton) -> bool
		{
			if (InSlotPos == InButton->GetSlotPosition())
			{
				// highlight button at specific slot
				InButton->SetHighLight(true);
			}
			else
			{
				// cancel highlight for other button
				InButton->SetHighLight(false);
			}

			return false;
		});
}

UUI_CharacterButton* UUI_CharacterSelectionList::GetHighlightButton()
{
	return FindByPredicateInList<UUI_CharacterButton>([](UUI_CharacterButton* InButton) -> bool
		{
			if (InButton->IsHighLight())
				return true;
			else
				return false;
		});
}

void UUI_CharacterSelectionList::JoinDSServer(int32 InSlotPos)
{
	if (UUI_RoleHallMain* UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		UI_RoleHallMain->JoinDSServer(InSlotPos);
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
				if (UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(List->AddChild(CharacterButton)))
				{
					// Set slot padding
					ScrollBoxSlot->SetPadding(10.f);
				}

				// Set Button Slot
				CharacterButton->SetSlotPosition(i);
				// Set Button's parent to CharacterList
				CharacterButton->SetWidgetParent(this);

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
