// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"

#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel

#include "Kismet/GameplayStatics.h"

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
			BindNetClientRcv();
		}
	}

	// Read Account & encrypted Passwd from local path
	if (!UI_Login->DecryptFromLocal(FPaths::ProjectDir() / TEXT("UserBackup")))
	{
		PrintMsgLog(TEXT("No logged account detected. Please input account & password."));
	}
	else
	{
		PrintMsgLog(TEXT("Autoload saved account."));
	}

	// Play MsgLog showup animation
	PlayWidgetAnim(TEXT("ShowUp"));
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

void UUI_LoginMain::PrintMsgLog(const FString& InMsgString)
{
	PrintMsgLog(FText::FromString(InMsgString));
}

void UUI_LoginMain::PrintMsgLog(const FText& InMsgText)
{
	UI_MsgLog->SetText(InMsgText);

	UI_MsgLog->PlayTextAnim();
}

void UUI_LoginMain::BindNetClientRcv()
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

void UUI_LoginMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_LoginResponses:
		{
			// Get Response Msg
			ELoginType ResponseType = ELoginType::DB_ERROR;
			FString UserDataJson;
			FMMOARPGGateStatus GateStatus;

			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginResponses, ResponseType, UserDataJson, GateStatus);

			switch (ResponseType)
			{
			case ELoginType::LOGIN_SUCCESS:
				// Save User Data to Game Instance
				if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
				{
					if (UserDataJson != TEXT("{}"))
					{
						NetDataParser::JsonToUserdata(UserDataJson, MMOARPGGameInstance->GetUserData());
					}

					// Encrypt Passwd and Store Account & encrypted Passwd to local path
					if (!UI_Login->EncryptToLocal(FPaths::ProjectDir() / TEXT("UserBackup")))
					{
						PrintMsgLog(TEXT("Password storage failed!"));
					}
					else
					{
						PrintMsgLog(TEXT("Login Success. Welcome~"));
					}

					if (GateStatus.GateConnectionNum == INDEX_NONE)
					{
						PrintMsgLog(TEXT("Server Online is FULL! Please try again later."));
					}
					else
					{
						MMOARPGGameInstance->GetGateStatus() = GateStatus;

						// Play MsgLog showoff animation
						PlayWidgetAnim(TEXT("ShowOff"));

						// Switch to Role Hall
						// Step1: close net client to login server
						if (MMOARPGGameInstance->GetNetClient() && MMOARPGGameInstance->GetNetClient()->GetChannel())
						{
							MMOARPGGameInstance->GetNetClient()->GetChannel()->DestroySelf();
						}
						// Step2: coroutine to switch to Role Hall Level
						GThread::Get()->GetCoroutines().BindLambda(2.f, [&]()
							{
								UGameplayStatics::OpenLevel(GetWorld(), TEXT("RoleHallMap"));
							}
						);
					}
				}
				break;
			case ELoginType::LOGIN_ACCOUNT_ERROR:
				PrintMsgLog(TEXT("Wrong Account!"));
				break;
			case ELoginType::LOGIN_PASSWORD_ERROR:
				PrintMsgLog(TEXT("Wrong Password!"));
				break;
			case ELoginType::DB_ERROR:
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
		UI_LoginLoading->SetVisibility(ESlateVisibility::Collapsed);
	}
}
