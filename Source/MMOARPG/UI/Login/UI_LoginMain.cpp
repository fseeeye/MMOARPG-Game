// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"
#include "UI_Login.h"

#include "Kismet/GameplayStatics.h"

// Plugins
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel

#include "../../MMOARPGMacro.h"

// run when UI created
void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	UI_Login->SetWidgetParent(this);

	LinkServer();

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
