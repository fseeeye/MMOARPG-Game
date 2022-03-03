// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_MainBase.h"
#include "../../MMOARPGMacro.h"

#if MMOARPG_DEBUG_DS
#include "../../Robot/MMOARPGTestRobot.h"
#endif

#include "UI_GameMain.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_GameMain : public UUI_MainBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) override;
	virtual void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg) override;

protected:
#if MMOARPG_DEBUG_DS
	FMMOARPGTestRobot Robot;
#endif
};
