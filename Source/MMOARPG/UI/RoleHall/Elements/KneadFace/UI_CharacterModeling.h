// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_Base.h"
#include "UI_CharacterModeling.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterModeling : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ModelingDefaults;

	UPROPERTY(meta = (BindWidget))
	class USlider* LegSlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LegValue;

	UPROPERTY(meta = (BindWidget))
	class USlider* WaistSlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaistValue;

	UPROPERTY(meta = (BindWidget))
	class USlider* ArmSlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ArmValue;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void UpdateCharacterStage();
	void UpdateTextBlock(UTextBlock* InTextBlock, float InValue);

	UFUNCTION()
	void LegValueChanged(float InValue);

	UFUNCTION()
	void WaistValueChanged(float InValue);

	UFUNCTION()
	void ArmValueChanged(float InValue);

	UFUNCTION()
	void SelectModelingDefaults(FString SelectedItem, ESelectInfo::Type SelectionType);
};
