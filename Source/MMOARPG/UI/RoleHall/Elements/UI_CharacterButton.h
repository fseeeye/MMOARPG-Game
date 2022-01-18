// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "UI_CharacterButton.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterButton : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UButton* CharacterButton;

	UPROPERTY(meta = (BindWidget))
	UImage* CreationIcon;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CharacterInfo;

	UPROPERTY(meta = (BindWidget))
	UImage* CharacterAvatar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CreationTime;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void ClickedCharacterButton();
};
