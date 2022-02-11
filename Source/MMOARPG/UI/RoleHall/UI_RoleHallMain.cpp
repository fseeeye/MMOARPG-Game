// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RoleHallMain.h"

#include "../../MMOARPGMacro.h"
#include "../../MMOARPGGameInstance.h"
#include "../../Core/RoleHall/RoleHallPlayerState.h"

#include "Kismet/GameplayStatics.h"

#include "MMOARPGCommType.h" // Plugin: MMOARPGComm
#include "Protocol/RoleHallProtocol.h" // Plugin: MMOARPGComm
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel

#define LOCTEXT_NAMESPACE "RoleHallMain"


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

void UUI_RoleHallMain::ResetCharacterSelectionList(bool bSpawnCharacter /*= true*/)
{
	// Recreate Character Buttons
	UI_CharacterSelectionList->CreateCharacterButtons();

	if (bSpawnCharacter)
	{
		// Spawn recent Character
		SpawnRecentCharacter();
	}

	// Highlight Button
	HightLightDefaultSelectButton();
}

void UUI_RoleHallMain::CheckCharacterNameInServer(FString& InCharacterName)
{
	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		SEND_DATA(SP_CheckCharacterNameRequests, MMOARPGGameInstance->GetUserData().ID, InCharacterName);
	}
}

void UUI_RoleHallMain::CreateCharacterInServer(const FMMOARPGCharacterAppearance& InCA)
{
	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// send character appearance json to server
		FString CAJson;
		NetDataParser::CharacterAppearanceToJson(InCA, CAJson);
		SEND_DATA(SP_CreateCharacterRequests, MMOARPGGameInstance->GetUserData().ID, CAJson);
	}
}

void UUI_RoleHallMain::PrintMsgLogCheckName(ECheckNameType InCheckNameType)
{
	switch (InCheckNameType)
	{
	case ECheckNameType::NAME_NOT_EXIST:
		PrintMsgLog(LOCTEXT("CHECK_NAME_NOT_EXIST", "The name is valid~"));
		break;
	case ECheckNameType::NAME_EXIST:
		PrintMsgLog(LOCTEXT("CHECK_NAME_EXIST", "The name is existed!"));
		break;
	case ECheckNameType::DB_ERROR:
		PrintMsgLog(LOCTEXT("CHECK_NAME_DB_ERROR", "DB check name error occured!"));
		break;
	case ECheckNameType::UNKNOW_ERROR:
		PrintMsgLog(LOCTEXT("CHECK_NAME_UNKNOW_ERROR", "Unknow check name error occured!"));
		break;
	default:
		break;
	}
}

void UUI_RoleHallMain::JoinDSServer(int32 InSlotPos)
{
	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// if handshake success, request character appearances.
		SEND_DATA(SP_LoginToDSServerRequests, MMOARPGGameInstance->GetUserData().ID, InSlotPos);
	}
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
					// Spawn recent played Character
					SpawnRecentCharacter();
					// HightLight Button
					HightLightDefaultSelectButton();
				}
			}

			break;
		}
		case SP_CheckCharacterNameResponses:
		{
			ECheckNameType CheckNameType = ECheckNameType::UNKNOW_ERROR;
			SIMPLE_PROTOCOLS_RECEIVE(SP_CheckCharacterNameResponses, CheckNameType);

			PrintMsgLogCheckName(CheckNameType);

			break;
		}
		case SP_CreateCharacterResponses:
		{
			ECheckNameType CheckNameType = ECheckNameType::UNKNOW_ERROR;
			bool bCreateCharacter = false;
			FString CharacterAppearancesJson;
			SIMPLE_PROTOCOLS_RECEIVE(SP_CreateCharacterResponses, CheckNameType, bCreateCharacter, CharacterAppearancesJson);

			if (CheckNameType == ECheckNameType::NAME_NOT_EXIST)
			{
				if (bCreateCharacter)
				{
					FMMOARPGCharacterAppearance NewCA = FMMOARPGCharacterAppearance();
					NetDataParser::JsonToCharacterAppearance(CharacterAppearancesJson, NewCA);
					if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
					{
						// Add new character appearance to PlayerState
						RoleHallPlayerState->AddCharacterAppearance(NewCA);

						// Play Name Box Show Off animation
						PlayNameBoxShowOffAnim();
						// Reset Selection List
						ResetCharacterSelectionList(false);

						PrintMsgLog(LOCTEXT("CREATE_CHARACTER_SUCCESS", "Create success."));
						break;
					}
				}

				PrintMsgLog(LOCTEXT("CREATE_CHARACTER_FAIL", "Create failed!"));
			}
			else
			{
				PrintMsgLogCheckName(CheckNameType);
			}

			break;
		}
		case SP_LoginToDSServerResponses:
		{
			FSimpleAddr DSServerAddr;
			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginToDSServerResponses, DSServerAddr);

			// Switch to Game Level
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameMap"));
	
			break;
		}
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

void UUI_RoleHallMain::SpawnRecentCharacter()
{
	if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
	{
		// Get & Spawn recent character appearance
		if (FMMOARPGCharacterAppearance* RecentCA = RoleHallPlayerState->GetRecentCharacterAppearance())
		{
			UI_CharacterSelectionList->SpawnCharacterStage(RecentCA);
		}
	}
}

void UUI_RoleHallMain::HightLightDefaultSelectButton()
{
	if (ARoleHallPlayerState* RoleHallPlayerState = GetPlayerState<ARoleHallPlayerState>())
	{
		// Get recent character appearance
		if (FMMOARPGCharacterAppearance* RecentCA = RoleHallPlayerState->GetRecentCharacterAppearance())
		{
			UI_CharacterSelectionList->HighlightButton(RecentCA->SlotPos);
		}
	}
}

#undef LOCTEXT_NAMESPACE
