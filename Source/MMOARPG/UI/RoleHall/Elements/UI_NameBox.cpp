// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_NameBox.h"

#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "../UI_RoleHallMain.h"
#include "../../../Core/RoleHall/RoleHallPawn.h"
#include "../../../Core/RoleHall/Character/RoleHallCharacterStage.h"


void UUI_NameBox::NativeConstruct()
{
	Super::NativeConstruct();

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

}

void UUI_NameBox::ClickedCreate()
{
	if (auto UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		// Play Name Box Show Off animation
		UI_RoleHallMain->PlayNameBoxShowOffAnim();
		// Reset Selection List
		UI_RoleHallMain->ResetCharacterSelectionList();
	}
}

void UUI_NameBox::ClickedCancel()
{
	if (auto UI_RoleHallMain = GetWidgetParent<UUI_RoleHallMain>())
	{
		//// Destory character
		//if (ARoleHallPawn* RoleHallPawn = GetPawn<ARoleHallPawn>())
		//{
		//	// if Character already exits, destroy it.
		//	if (RoleHallPawn->RoleHallCharacterStage)
		//	{
		//		RoleHallPawn->RoleHallCharacterStage->Destroy();
		//		RoleHallPawn->RoleHallCharacterStage = nullptr;
		//	}
		//}
		// Play Name Box Show Off animation
		UI_RoleHallMain->PlayNameBoxShowOffAnim();
		// Reset Selection List & Spawn recent Character
		UI_RoleHallMain->ResetCharacterSelectionList();
	}
}
