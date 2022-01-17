// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RoleHallMain.h"

#include "../../MMOARPGGameInstance.h"

#include "MMOARPGCommType.h" // Plugin: MMOARPGComm
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel

void UUI_RoleHallMain::NativeConstruct()
{
	Super::NativeConstruct();

	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (MMOARPGGameInstance->GetNetClient())
		{
			// Connect to Gate Server
			MMOARPGGameInstance->GetNetClient()->Init(MMOARPGGameInstance->GetGateStatus().GateAddrInfo.Addr);

			BindNetClientRcv();
		}
	}
}

void UUI_RoleHallMain::NativeDestruct()
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

void UUI_RoleHallMain::PrintMsgLog(const FString& InMsgString)
{
	PrintMsgLog(FText::FromString(InMsgString));
}

void UUI_RoleHallMain::PrintMsgLog(const FText& InMsgText)
{
	UI_MsgLog->SetText(InMsgText);

	UI_MsgLog->PlayTextAnim();
}

void UUI_RoleHallMain::BindNetClientRcv()
{
	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (MMOARPGGameInstance->GetNetClient() && MMOARPGGameInstance->GetNetClient()->GetController())
		{
			RecvDelegate = MMOARPGGameInstance->GetNetClient()->GetController()->RecvDelegate.AddLambda(
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

void UUI_RoleHallMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	//switch (ProtocolNumber)
	//{
	//default:
	//	break;
	//}
}
