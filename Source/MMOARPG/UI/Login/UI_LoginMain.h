// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"

#include "SimpleNetChannelType.h"

#include "UI_LoginMain.generated.h"

class FSimpleChannel;
/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_LoginMain : public UUI_Base
{
	GENERATED_BODY()

	// Link UI Widget
	UPROPERTY(meta = (BindWidget))
	UUserWidget* UI_LinkWidget;
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	void BindClientRcvLoop();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) override;

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);
private:
	FDelegateHandle RecvDelegate;
};
