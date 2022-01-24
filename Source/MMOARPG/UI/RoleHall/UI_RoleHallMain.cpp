// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RoleHallMain.h"

#include "../../MMOARPGMacro.h"
#include "../../MMOARPGGameInstance.h"
#include "../../Core/RoleHall/RoleHallPlayerState.h"

#include "MMOARPGCommType.h" // Plugin: MMOARPGComm
#include "Protocol/RoleHallProtocol.h" // Plugin: MMOARPGComm
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel


void UUI_RoleHallMain::NativeConstruct()
{
	Super::NativeConstruct();

	// Set Widgets parent to RoleHall
	UI_CharacterSelectionList->SetWidgetParent(this); 
	UI_NameBox->SetWidgetParent(this);

	// Init Gate Server Connection
	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (MMOARPGGameInstance->GetNetClient())
		{
			// Bind Client Handshake Handler
			MMOARPGGameInstance->GetNetClient()->NetManageMsgDelegate.BindUObject(this, &UUI_RoleHallMain::LinkServerInfo);
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
	switch (ProtocolNumber)
	{
	case SP_CharacterAppearancesResponses:
	{
		FString CharacterAppearancesJson;
		SIMPLE_PROTOCOLS_RECEIVE(SP_CharacterAppearancesResponses, CharacterAppearancesJson);

		if (!CharacterAppearancesJson.IsEmpty())
		{
			if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
			{
				// Deserialize and save character appearances to Player State
				NetDataParser::JsonToCharacterAppearances(CharacterAppearancesJson, RoleHallPlayerState->GetCharacterAppearances());
				// Create Character Buttons
				UI_CharacterSelectionList->CreateCharacterButtons();
			}
		}

		break;
	}
	default:
		break;
	}
}

void UUI_RoleHallMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
		{
			// if handshake success, request character appearances.
			SEND_DATA(SP_CharacterAppearancesRequests, MMOARPGGameInstance->GetUserData().ID);
		}
	}
}
