// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"

// Plugins
#include "SimpleNetChannelType.h"
#include "MMOARPGCommType.h"

#include "UI_MainBase.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_MainBase : public UUI_Base
{
	GENERATED_BODY()

	// Import MsgLog UI Widget
	UPROPERTY(meta = (BindWidget))
	class UUI_MsgLog* UI_MsgLog;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void PrintMsgLog(const FString& InMsgString);
	void PrintMsgLog(const FText& InMsgText);

protected:
	void BindNetClientRcv();

	void LinkServer();
	void LinkServer(const FSimpleAddr& InAddr);

	UFUNCTION()
	virtual void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg) {}

private:
	FDelegateHandle RecvDelegate;
};
