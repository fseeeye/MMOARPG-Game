// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_MainBase.h"
#include "UI_LoginMain.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_LoginMain : public UUI_MainBase
{
	GENERATED_BODY()

	// Import Loading UI Widget
	UPROPERTY(meta = (BindWidget))
	UUserWidget* UI_LoginLoading;

	// Import Login UI Widget
	UPROPERTY(meta = (BindWidget))
	class UUI_Login* UI_Login;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	void SignIn(FString& InAccount, FString& InPassword);
	// TODO
	void SignUp();

protected:
	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) override;
	virtual void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg) override;

private:
	FDelegateHandle RecvDelegate;
};
