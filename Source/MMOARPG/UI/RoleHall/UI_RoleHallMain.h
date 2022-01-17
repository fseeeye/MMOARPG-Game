// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"

#include "SimpleNetChannelType.h" // Plugin: SimpleNetChannel

#include "../Universal/UI_MsgLog.h"

#include "UI_RoleHallMain.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_RoleHallMain : public UUI_Base
{
	GENERATED_BODY()

	// Import MsgLog UI Widget
	UPROPERTY(meta = (BindWidget))
	UUI_MsgLog* UI_MsgLog;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	void PrintMsgLog(const FString& InMsgString);
	void PrintMsgLog(const FText& InMsgText);

protected:
	void BindNetClientRcv();
	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

private:
	FDelegateHandle RecvDelegate;
};
