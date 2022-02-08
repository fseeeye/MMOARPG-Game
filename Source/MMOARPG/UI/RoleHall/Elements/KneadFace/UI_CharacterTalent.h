// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_Base.h"
#include "UI_CharacterTalent.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterTalent : public UUI_Base
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
