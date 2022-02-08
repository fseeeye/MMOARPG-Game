// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterAppearance.h"

// Widgets
#include "Components/ComboBoxString.h"
#include "Components/WrapBox.h"

void UUI_CharacterAppearance::NativeConstruct()
{
	Super::NativeConstruct();

	AppearanceDefaults->OnSelectionChanged.AddDynamic(this, &UUI_CharacterAppearance::SelectAppearanceDefaults);
}

void UUI_CharacterAppearance::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterAppearance::SelectAppearanceDefaults(FString SelectedItem, ESelectInfo::Type SelectionType)
{

}
