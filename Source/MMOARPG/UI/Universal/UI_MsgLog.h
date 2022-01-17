// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"

#include "Components/TextBlock.h"

#include "UI_MsgLog.generated.h"

//class UTextBlock;
/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_MsgLog : public UUI_Base
{
	GENERATED_BODY()
	
	// Import MsgLog UI Widget
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MsgLog;

public:
	void PlayTextAnim();
	void SetText(const FText& InText);
};
