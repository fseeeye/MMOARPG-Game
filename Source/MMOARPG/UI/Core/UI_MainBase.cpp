// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainBase.h"

#include "../../MMOARPGMacro.h"

// Plugins
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel

// Components
#include "../Universal/UI_MsgLog.h"


void UUI_MainBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_MainBase::NativeDestruct()
{
	Super::NativeDestruct();

	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (MMOARPGGameInstance->GetNetClient() && MMOARPGGameInstance->GetNetClient()->GetController())
		{
			MMOARPGGameInstance->GetNetClient()->GetController()->RecvDelegate.Remove(RecvDelegate);
		}
	}
}

void UUI_MainBase::PrintMsgLog(const FString& InMsgString)
{
	PrintMsgLog(FText::FromString(InMsgString));
}

void UUI_MainBase::PrintMsgLog(const FText& InMsgText)
{
	UI_MsgLog->SetText(InMsgText);

	UI_MsgLog->PlayTextAnim();
}

void UUI_MainBase::BindNetClientRcv()
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
			// coroutine: wait for 0.5s and try again
			GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindNetClientRcv(); });
		}
	}
	else
	{
		// coroutine: wait for 0.5s and try again
		GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]() { BindNetClientRcv(); });
	}
}

void UUI_MainBase::LinkGateServer()
{
	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// Create Net Client
		InGameInstance->CreateNetClient();

		if (InGameInstance->GetNetClient())
		{
			// Bind Client Handshake Handler
			InGameInstance->GetNetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_MainBase::LinkServerInfo);
			// Link to Server
			InGameInstance->LinkServer();
			// Bind Client Recv
			BindNetClientRcv();
		}
	}
}

void UUI_MainBase::LinkGateServer(const FSimpleAddr& InAddr)
{
	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// Create Net Client
		InGameInstance->CreateNetClient();

		if (InGameInstance->GetNetClient())
		{
			// Bind Client Handshake Handler
			InGameInstance->GetNetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_MainBase::LinkServerInfo);
			// Link to Server
			InGameInstance->LinkServer(InAddr);
			// Bind Client Recv
			BindNetClientRcv();
		}
	}
}
