// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_Base.h"
#include "UI_SkinColorButton.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_SkinColorButton : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ColorButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* ColorImage;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void ColorButtonClicked();
};
