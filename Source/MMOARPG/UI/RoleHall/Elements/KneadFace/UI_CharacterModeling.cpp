// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_CharacterModeling.h"

#include "../../../../Core/RoleHall/RoleHallPlayerState.h"
#include "../../../../Core/RoleHall/RoleHallPawn.h"
#include "../../../../Core/RoleHall/Character/RoleHallCharacterStage.h"

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

void UUI_CharacterModeling::UpdateCharacterStage()
{
	// Update Kneading Model Attributes & Temp CA in PlayerState
	if (ARoleHallPawn* RoleHallPawn = GetPawn<ARoleHallPawn>())
	{
		if (ARoleHallPlayerState* RoleHallPlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ARoleHallPlayerState>())
		{
			if (RoleHallPawn->RoleHallCharacterStage)
			{
				int32 slotPos = RoleHallPawn->RoleHallCharacterStage->GetSlotPos();
				//FMMOARPGCharacterAppearance* CA = RoleHallPlayerState->GetCharacterAppearanceWithPos(slotPos);
				//if (!CA)
				//{
				//	// It's a empty CA
				//	if (auto* TmpCA = RoleHallPlayerState->GetTmpCharacterAppearance())
				//	{
				//		if (TmpCA->SlotPos == slotPos)
				//		{
				//			CA = TmpCA;
				//		}
				//	}
				//}
				auto* TmpCA = RoleHallPlayerState->GetTmpCharacterAppearance();
				if (TmpCA->SlotPos == slotPos)
				{
					if (TmpCA)
					{
						TmpCA->LegSize = LegSlider->GetValue() * 6.f;
						TmpCA->WaistSize = WaistSlider->GetValue() * 6.f;
						TmpCA->ArmSize = ArmSlider->GetValue() * 6.f;
						//...
					}

					RoleHallPawn->RoleHallCharacterStage->UpdateKneadingModelAttributes();
				}
			}
		}
	}
}

void UUI_CharacterModeling::UpdateTextBlock(UTextBlock* InTextBlock, float InValue)
{
	if (InTextBlock)
	{
		int32 IntValue = InValue * 6; // 0 - 6
		// Change showing text value
		InTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), IntValue)));
	}
}

void UUI_CharacterModeling::LegValueChanged(float InValue)
{
	UpdateTextBlock(LegValue, InValue);
	UpdateCharacterStage();
}

void UUI_CharacterModeling::WaistValueChanged(float InValue)
{
	UpdateTextBlock(WaistValue, InValue);
	UpdateCharacterStage();
}

void UUI_CharacterModeling::ArmValueChanged(float InValue)
{
	UpdateTextBlock(ArmValue, InValue);
	UpdateCharacterStage();
}

void UUI_CharacterModeling::SelectModelingDefaults(FString SelectedItem, ESelectInfo::Type SelectionType)
{

}
