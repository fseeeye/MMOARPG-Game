// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"

#include "ThreadManage.h"
#include "UObject/SimpleController.h"

#include "../../MMOARPGGameInstance.h"

// run when UI created
void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// Create Client
		InGameInstance->CreateNetClient();
		if (InGameInstance->GetNetClient())
		{
			// Bind Client Handshake Handler
			InGameInstance->GetNetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_LoginMain::LinkServerInfo);
			// Link to Server
			InGameInstance->LinkServer();
			// Bind Client Recv
			BindClientRcvLoop();
		}
	}
}

// run when UI closed
void UUI_LoginMain::NativeDestruct()
{
	Super::NativeDestruct();

	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (InGameInstance->GetNetClient() && InGameInstance->GetNetClient()->GetController())
		{
			InGameInstance->GetNetClient()->GetController()->RecvDelegate.Remove(RecvDelegate);
		}
	}
}

void UUI_LoginMain::BindClientRcvLoop()
{
	// Wait for Game Instance complete creation, and then, bind client recv channel
	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (InGameInstance->GetNetClient() && InGameInstance->GetNetClient()->GetController())
		{
			RecvDelegate = InGameInstance->GetNetClient()->GetController()->RecvDelegate.AddLambda(
				[&](uint32 ProtocolNumber, FSimpleChannel* Channel)
				{
					this->RecvProtocol(ProtocolNumber, Channel);
				}
			);
		}
		else
		{
			// coroutine
			GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcvLoop(); });
		}
	}
	else
	{
		// coroutine
		GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindClientRcvLoop(); });
	}
}

void UUI_LoginMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{

}

void UUI_LoginMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		// if handshake success, hide Link UI widget
		UI_LinkWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
