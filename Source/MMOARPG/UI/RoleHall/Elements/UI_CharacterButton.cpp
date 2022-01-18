// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterButton.h"

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

}
