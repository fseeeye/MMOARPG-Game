// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TextBlock.h"
#include "SimpleNetChannelType.h"

#include "../Core/UI_Base.h"
#include "UI_Login.h"

#include "UI_LoginMain.generated.h"

class FSimpleChannel;
/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_LoginMain : public UUI_Base
{
	GENERATED_BODY()

	// Import Loading UI Widget
	UPROPERTY(meta = (BindWidget))
	UUserWidget* UI_Loading;

	// Import Login UI Widget
	UPROPERTY(meta = (BindWidget))
	UUI_Login* UI_Login;
	
	// Import Login UI Widget
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MsgLog;

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

public:
	void SignIn(FString& InAccount, FString& InPassword);

	// TODO
	void SignUp();

	void PrintMsgLog(const FString& InMsg);

protected:
	void BindClientRcvLoop();

	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) override;

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);
private:
	FDelegateHandle RecvDelegate;
};
