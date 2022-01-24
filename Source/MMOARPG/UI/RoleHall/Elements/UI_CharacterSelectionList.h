// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"

#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "UI_CharacterButton.h"
#include "UI_KneadFace.h"
#include "MMOARPGCommType.h"

#include "UI_CharacterSelectionList.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterSelectionList : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ListName;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* List;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUI_CharacterButton> UI_CharacterButtonSubClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUI_KneadFace> UI_KneadFaceSubClass;
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void CreateKneadFacePanel();
	void CreateCharacterButtons();

protected:
	void InitCharacterButtons(FMMOARPGCharacterAppearances& InCAs);
};
