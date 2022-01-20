// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_NameBox.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_NameBox : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* CharacterName;

	UPROPERTY(meta = (BindWidget))
	class UButton* VerifyNameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreationButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void ClickedVerify();

	UFUNCTION()
	void ClickedCreate();

	UFUNCTION()
	void ClickedCancel();
};
