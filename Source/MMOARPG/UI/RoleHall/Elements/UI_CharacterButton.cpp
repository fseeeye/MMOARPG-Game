// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "../../../Core/RoleHall/RoleHallPawn.h"

void UUI_CharacterButton::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterButton->OnReleased.AddDynamic(this, &UUI_CharacterButton::ClickedCharacterButton);

	// Set Widgets default Visibility
	CreationIcon->SetVisibility(ESlateVisibility::Visible);
	CharacterInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void UUI_CharacterButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterButton::ClickedCharacterButton()
{
	// Get RoleHall Pawn
	if (ARoleHallPawn* RoleHallPawn = GetPawn<ARoleHallPawn>())
	{
		if (RoleHallCharacterStageClass)
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
}
