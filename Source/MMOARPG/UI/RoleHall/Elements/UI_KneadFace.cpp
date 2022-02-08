// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_KneadFace.h"

// Widgets
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"

void UUI_KneadFace::NativeConstruct()
{
	Super::NativeConstruct();

	Modeling->OnCheckStateChanged.AddDynamic(this, &UUI_KneadFace::OnClickedModeling);
	Appearance->OnCheckStateChanged.AddDynamic(this, &UUI_KneadFace::OnClickedAppearance);
	Talent->OnCheckStateChanged.AddDynamic(this, &UUI_KneadFace::OnClickedTalent);

	Modeling->SetCheckedState(ECheckBoxState::Checked);
}

void UUI_KneadFace::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_KneadFace::OnClickedModeling(bool bIsChecked)
{
	Modeling->SetCheckedState(ECheckBoxState::Checked);
	Appearance->SetCheckedState(ECheckBoxState::Unchecked);
	Talent->SetCheckedState(ECheckBoxState::Unchecked);

	KneadPanel->SetActiveWidgetIndex(0);
}

void UUI_KneadFace::OnClickedAppearance(bool bIsChecked)
{
	Modeling->SetCheckedState(ECheckBoxState::Unchecked);
	Appearance->SetCheckedState(ECheckBoxState::Checked);
	Talent->SetCheckedState(ECheckBoxState::Unchecked);

	KneadPanel->SetActiveWidgetIndex(1);
}

void UUI_KneadFace::OnClickedTalent(bool bIsChecked)
{
	Modeling->SetCheckedState(ECheckBoxState::Unchecked);
	Appearance->SetCheckedState(ECheckBoxState::Unchecked);
	Talent->SetCheckedState(ECheckBoxState::Checked);

	KneadPanel->SetActiveWidgetIndex(2);
}
