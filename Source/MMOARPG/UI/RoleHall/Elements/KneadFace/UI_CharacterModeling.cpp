// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterModeling.h"

// Widgets
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void UUI_CharacterModeling::NativeConstruct()
{
	Super::NativeConstruct();

	ModelingDefaults->OnSelectionChanged.AddDynamic(this, &UUI_CharacterModeling::SelectModelingDefaults);

	LegSlider->OnValueChanged.AddDynamic(this, &UUI_CharacterModeling::LegValueChanged);
	WaistSlider->OnValueChanged.AddDynamic(this, &UUI_CharacterModeling::WaistValueChanged);
	ArmSlider->OnValueChanged.AddDynamic(this, &UUI_CharacterModeling::ArmValueChanged);
}

void UUI_CharacterModeling::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterModeling::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_CharacterModeling::LegValueChanged(float InDeltaValue)
{

}

void UUI_CharacterModeling::WaistValueChanged(float InDeltaValue)
{

}

void UUI_CharacterModeling::ArmValueChanged(float InDeltaValue)
{

}

void UUI_CharacterModeling::SelectModelingDefaults(FString SelectedItem, ESelectInfo::Type SelectionType)
{

}
