// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_NameBox.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "../UI_RoleHallMain.h"
#include "../../../Core/RoleHall/RoleHallPawn.h"
#include "../../../Core/RoleHall/Character/RoleHallCharacterStage.h"
#include "../../../Core/RoleHall/RoleHallPlayerState.h"
#include "MMOARPGCommType.h"


void UUI_NameBox::NativeConstruct()
{
	Super::NativeConstruct();

	SlotPosition = INDEX_NONE;

	VerifyNameButton->OnReleased.AddDynamic(this, &UUI_NameBox::ClickedVerify);
	CreationButton->OnReleased.AddDynamic(this, &UUI_NameBox::ClickedCreate);
	CancelButton->OnReleased.AddDynamic(this, &UUI_NameBox::ClickedCancel);
}

void UUI_NameBox::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_NameBox::ClickedVerify()
{
	if (auto UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		FString Name = CharacterName->GetText().ToString();
		// Send Check Character Name Request
		UI_RoleHallMain->CheckCharacterNameInServer(Name);
	}
}

void UUI_NameBox::ClickedCreate()
{
	if (auto UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		if (auto* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
		{
			if (auto* TmpCA = RoleHallPlayerState->GetTmpCharacterAppearance())
			{
				TmpCA->Name = CharacterName->GetText().ToString();
				TmpCA->CreationDate = FDateTime::Now().ToString();

				if (TmpCA->Name.IsEmpty())
				{
					UI_RoleHallMain->PrintMsgLog(TEXT("Please input characeter name."));
				}
				else
				{
					// Send Create Character Request
					UI_RoleHallMain->CreateCharacterInServer(*TmpCA);
				}
			}
		}
	}
}

void UUI_NameBox::ClickedCancel()
{
	if (auto UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		// Destory tmp character
		if (ARoleHallPawn* RoleHallPawn = GetPawn<ARoleHallPawn>())
		{
			// if Character already exits, destroy it.
			if (RoleHallPawn->RoleHallCharacterStage)
			{
				RoleHallPawn->RoleHallCharacterStage->Destroy();
				RoleHallPawn->RoleHallCharacterStage = nullptr;
			}
		}
		// Play Name Box Show Off animation
		UI_RoleHallMain->PlayNameBoxShowOffAnim();
		// Reset Selection List & Spawn recent Character
		UI_RoleHallMain->ResetCharacterSelectionList();
	}
}
