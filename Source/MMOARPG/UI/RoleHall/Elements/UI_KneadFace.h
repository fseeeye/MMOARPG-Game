// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_KneadFace.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_KneadFace : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* Modeling;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* Appearance;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* Talent;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* KneadPanel;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnClickedModeling(bool bIsChecked);

	UFUNCTION()
	void OnClickedAppearance(bool bIsChecked);

	UFUNCTION()
	void OnClickedTalent(bool bIsChecked);
};
