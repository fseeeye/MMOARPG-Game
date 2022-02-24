// Copyright Epic Games, Inc. All Rights Reserved.

#include "MMOARPGGameMode.h"

#include "../../MMOARPGMacro.h"
#include "MMOARPGHUD.h"
#include "MMOARPGGameState.h"
#include "MMOARPGPlayerState.h"
#include "Character/MMOARPGCharacter.h"
#include "Character/MMOARPGPlayerCharacter.h"
#include "Utils/MethodUnit.h"

#include "UObject/ConstructorHelpers.h"

// Plugins
#include "ThreadManage.h" // Plugin: SimpleThread
#include "UObject/SimpleController.h" // Plugin: SimpleNetChannel
#include "MMOARPGCommType.h" // Plugin: MMOARPGComm
#include "Protocol/GameProtocol.h" // Plugin: MMOARPGComm


AMMOARPGGameMode::AMMOARPGGameMode()
{
	// Register HUD
	HUDClass = AMMOARPGHUD::StaticClass();
	// Register GameState
	GameStateClass = AMMOARPGGameState::StaticClass();
	// Register PlayerState
	PlayerStateClass = AMMOARPGPlayerState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMMOARPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Link Center Server
	LinkServer();
}

void AMMOARPGGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (UMMOARPGGameInstance* MMOARPGGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		if (MMOARPGGameInstance->GetNetClient() && MMOARPGGameInstance->GetNetClient()->GetController())
		{
			MMOARPGGameInstance->GetNetClient()->GetController()->RecvDelegate.Remove(RecvDelegate);
		}
	}
}

void AMMOARPGGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMMOARPGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Wait Client to sync
	GThread::Get()->GetCoroutines().BindLambda(0.5f, [&](APlayerController* InNewPlayer) {
		// Register SwitchState Animation TableRow
		/*if (InNewPlayer)
		{
			if (AMMOARPGPlayerCharacter* PlayerCharacter = InNewPlayer->GetPawn<AMMOARPGPlayerCharacter>())
			{
				if (AMMOARPGGameState* GameState = GetGameState<AMMOARPGGameState>())
				{
					if (FCharacterAnimTableRow* SwitchStateAnimTableRow = GameState->GetCharacterAnimTableRow(PlayerCharacter->GetSwitchStateAnimTableID()))
					{
						PlayerCharacter->SwitchStateAnimTableRow = SwitchStateAnimTableRow;
					}
				}
			}
		}*/
	}, NewPlayer);
}

// Get Kneading Data from Center Server
void AMMOARPGGameMode::UpdateKneadingDataRequest(int32 InUserID)
{
	SEND_DATA(SP_GetLoggedCharacterCaRequests, InUserID);
}

void AMMOARPGGameMode::BindNetClientRcv()
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

void AMMOARPGGameMode::LinkServer()
{
	if (UMMOARPGGameInstance* InGameInstance = GetGameInstance<UMMOARPGGameInstance>())
	{
		// Create Net Client
		InGameInstance->CreateNetClient();

		if (InGameInstance->GetNetClient())
		{
			// Bind Client Handshake Handler
			InGameInstance->GetNetClient()->NetManageMsgDelegate.BindUObject(this, &AMMOARPGGameMode::LinkServerInfo);
			// Link to Center Server
			//InGameInstance->LinkServer();
			InGameInstance->LinkServer(TEXT("127.0.0.1"), 11231); // TODO: use config file
			// Bind Client Recv
			BindNetClientRcv();
		}
	}
}

void AMMOARPGGameMode::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{

}

void AMMOARPGGameMode::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_GetLoggedCharacterCaResponses:
		{
			int32 UserID = INDEX_NONE;
			FString CAJson;
			SIMPLE_PROTOCOLS_RECEIVE(SP_GetLoggedCharacterCaResponses, UserID, CAJson);

			if (UserID != INDEX_NONE && !CAJson.IsEmpty())
			{
				FMMOARPGCharacterAppearance CA;
				NetDataParser::JsonToCharacterAppearance(CAJson, CA);

				// Traverse Pawns to update CA in target PlayerCharacter
				MethodUnit::CallAllPlayersOnServer<AMMOARPGPlayerCharacter>(GetWorld(), [&](AMMOARPGPlayerCharacter* InPlayerCharacter)->MethodUnit::EServerCallResult 
				{
					if (InPlayerCharacter->GetUserID() == UserID)
					{
						InPlayerCharacter->UpdateKneadingModelAttributes(CA); // Update CA on Server
						InPlayerCharacter->UpdateKneadingDataOnClient(CA);    // Update CA on primary Client (RPC)

						return MethodUnit::EServerCallResult::PROGRESS_COMPLETE;
					}
					
					return MethodUnit::EServerCallResult::INPROGRESS;
				});
			}

			break;
		}
	}
}
