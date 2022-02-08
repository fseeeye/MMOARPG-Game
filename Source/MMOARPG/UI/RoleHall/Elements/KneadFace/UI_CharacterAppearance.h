// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_Base.h"
#include "UI_CharacterAppearance.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterAppearance : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* AppearanceDefaults;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SkinWrap;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* ClothWrap;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* LegWrap;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void SelectAppearanceDefaults(FString SelectedItem, ESelectInfo::Type SelectionType);
};
