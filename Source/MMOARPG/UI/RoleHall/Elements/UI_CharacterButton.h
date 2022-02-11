// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"

#include "MMOARPGCommType.h" // Plugin: MMOARPGComm

#include "UI_CharacterButton.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterButton : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UButton* CharacterButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* CreationIcon;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* CharacterInfo;

	UPROPERTY(meta = (BindWidget))
	class UImage* CharacterAvatar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CreationDate;

	UPROPERTY(EditDefaultsOnly, Category = "HightLight")
	FLinearColor HightLightColor;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	FORCEINLINE int32 GetSlotPosition() { return SlotPosition; }
	FORCEINLINE void SetSlotPosition(const int32 InNewPos) { SlotPosition = InNewPos; }

	void InitWithCA(const FMMOARPGCharacterAppearance& InCA);

	void SetHighLight(bool bHighLight);
	FORCEINLINE bool IsHighLight();

	void JumpIntoGameLevel(int32 InSlotPos);

protected:
	UFUNCTION()
	void ClickedCharacterButton();

protected:
	int32 SlotPosition;
	FLinearColor DefaultColor;
};
