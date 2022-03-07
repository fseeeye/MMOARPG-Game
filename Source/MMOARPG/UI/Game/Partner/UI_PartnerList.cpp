// Fill out your copyright notice in the Description page of Project Settings.
#include "UI_PartnerList.h"
#include "UI_PartnerInfo.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UUI_PartnerList::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

void UUI_PartnerList::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUI_PartnerList::Init()
{
	if (UI_PartnerInfoClass)
	{
		// TMP: Create PartnerInfo Panels
		for (int32 i = 1; i < 3; ++i)
		{
			if (UUI_PartnerInfo* PartnerInfo = CreateWidget<UUI_PartnerInfo>(GetWorld(), UI_PartnerInfoClass))
			{
				PartnerInfo->SetWidgetParent(this);

				if (i == 1)
				{
					// Select Player Character by default.
					PartnerInfo->SetChecked(true);
				}

				if (UVerticalBoxSlot* BoxSlot = CharacterList->AddChildToVerticalBox(PartnerInfo))
				{
					BoxSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 10.f));
					PartnerInfo->SetCharacterID(i);
				}
			}
		}
	}
}

void UUI_PartnerList::TraverseListChildsByPredicate(TFunction<bool(UUI_PartnerInfo* InPartnerInfo)> InFunc)
{
	for (int i = 0; i < CharacterList->GetChildrenCount(); ++i)
	{
		if (UUI_PartnerInfo* PartnerInfo = Cast<UUI_PartnerInfo>(CharacterList->GetChildAt(i)))
		{
			if (!InFunc(PartnerInfo))
			{
				break;
			}
		}
	}
}
