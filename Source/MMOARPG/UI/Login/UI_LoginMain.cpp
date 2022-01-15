// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"

#include "ThreadManage.h"
#include "UObject/SimpleController.h"

#include "Protocol/LoginProtocol.h" // Plugin: MMOARPGComm

#include "../../MMOARPGGameInstance.h"
#include "../../MMOARPGMacro.h"

// run when UI created
void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	UI_Login->SetWidgetParent(this);

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

void UUI_LoginMain::SignIn(FString& InAccount, FString& InPassword)
{
	PrintMsgLog("Logging in...");

	// Send login info to Login Server
	SEND_DATA(SP_LoginRequests, InAccount, InPassword);
}

// TODO
void UUI_LoginMain::SignUp()
{

}

void UUI_LoginMain::PrintMsgLog(const FString& InMsg)
{
	// TODO: play animation

	MsgLog->SetText(FText::FromString(InMsg));
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
	switch (ProtocolNumber)
	{
		case SP_LoginResponses:
		{
			// Get Response Msg
			ELoginType ResponseType = ELoginType::DB_ERROR;
			FString UserDataJson;
			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginResponses, ResponseType, UserDataJson, GateStatus);

			switch (ResponseType)
			{
			case LOGIN_SUCCESS:
				PrintMsgLog(TEXT("Login Success. Welcome~"));

				// Save User Data to Game Instance
				if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
				{
					if (UserDataJson != TEXT("{}"))
					{
						NetDataParser::JsonToUserdata(UserDataJson, InGameInstance->GetUserData());
						// TODO: Jump to Hall
					}
				}

				break;
			case LOGIN_ACCOUNT_ERROR:
				PrintMsgLog(TEXT("Wrong Account!"));
				break;
			case LOGIN_PASSWORD_ERROR:
				PrintMsgLog(TEXT("Wrong Password!"));
				break;
			case DB_ERROR:
				PrintMsgLog(TEXT("DB Error!"));
				break;
			}

			break;
		}
	}
}

void UUI_LoginMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		// if handshake success, hide Loading UI widget
		UI_Loading->SetVisibility(ESlateVisibility::Collapsed);
	}
}
