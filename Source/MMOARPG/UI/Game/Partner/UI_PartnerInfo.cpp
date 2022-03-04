// Fill out your copyright notice in the Description page of Project Settings.
#include "UI_PartnerInfo.h"
#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "UI_PartnerInfo.h"

UUI_PartnerInfo::UUI_PartnerInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CharacterID(INDEX_NONE)
{
}

void UUI_PartnerInfo::NativeConstruct()
{
	Super::NativeConstruct();

	ClickedCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_PartnerInfo::OnClickedCharacter);
}

void UUI_PartnerInfo::NativeDestruct()
{
	Super::NativeDestruct();


}

void UUI_PartnerInfo::SetChecked(bool bChecked)
{
	ClickedCheckBox->SetCheckedState(bChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void UUI_PartnerInfo::OnClickedCharacter(bool bClicked)
{
	// Set self checked
	SetChecked(bClicked);

	// Set others unchecked
	if (UUI_PartnerList* PartnerList = GetWidgetParent<UUI_PartnerList>())
	{
		PartnerList->TraverseListChildsByPredicate([&](UUI_PartnerInfo* InPartnerInfo) -> bool
		{
			if (InPartnerInfo->GetCharacterID() != CharacterID)
			{
				InPartnerInfo->SetChecked(!bClicked);
			}

			return true;
		});
	}
}
