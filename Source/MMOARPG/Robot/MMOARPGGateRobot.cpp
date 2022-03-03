#include "MMOARPGGateRobot.h"

// Plugins
#include <Global/SimpleNetGlobalInfo.h>
#include <SimpleProtocolsDefinition.h>
#include <Protocol/RoleHallProtocol.h>
#include <UObject/SimpleController.h>


FMMOARPGGateRobot::FMMOARPGGateRobot()
	: GateClient(nullptr)
{
}

FMMOARPGGateRobot::~FMMOARPGGateRobot()
{
	if (GateClient)
	{
		FSimpleNetManage::Destroy(GateClient);
		GateClient = nullptr;
	}
}

void FMMOARPGGateRobot::Init(const FString& InHost, const int32 InPort)
{
	if (!GateClient)
	{
		// Init Net Channel
		FSimpleNetGlobalInfo::Get()->Init();
		// Create Game Net Client Instance
		GateClient = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_TCP);

		// Bind Client Handshake Handler
		GateClient->NetManageMsgDelegate.BindRaw(this, &FMMOARPGGateRobot::LinkServerInfo);

		// Init Connection
		if (!GateClient->Init(InHost, InPort))
		{
			delete GateClient;
			GateClient = nullptr;
		}

		// Bind Client Recv Channel
		GateClient->GetController()->RecvDelegate.AddLambda(
			[&](uint32 ProtocolNumber, FSimpleChannel* Channel)
			{
				RecvProtocol(ProtocolNumber, Channel);
			}
		);
	}
}

void FMMOARPGGateRobot::NativeTick(float DeltaTime)
{
	if (GateClient)
	{
		GateClient->Tick(DeltaTime);
	}
}

void FMMOARPGGateRobot::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	switch (ProtocolNumber)
	{
		case SP_CharacterAppearancesResponses:
		{
			FString CharacterAppearancesJson;
			SIMPLE_PROTOCOLS_RECEIVE(SP_CharacterAppearancesResponses, CharacterAppearancesJson);

			if (!CharacterAppearancesJson.IsEmpty())
			{
				// Step2: Send LoginToDSServerRequest
				RunLoginToDSServerRequest();
			}

			break;
		}
		case SP_LoginToDSServerResponses:
		{
			FSimpleAddr DSServerAddr;
			SIMPLE_PROTOCOLS_RECEIVE(SP_LoginToDSServerResponses, DSServerAddr);

			//FString DSAddrString = FSimpleNetManage::GetAddrString(DSServerAddr);

			StartDelegate.ExecuteIfBound();

			break;
		}
	}
}

void FMMOARPGGateRobot::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		// Step1: Send CharacterAppearanceRequests
		RunCharacterAppearanceRequests();
	}
}

void FMMOARPGGateRobot::RunCharacterAppearanceRequests()
{
	// it will register UserID in GateServer
	int32 UserID = 1;
	SIMPLE_CLIENT_SEND(GateClient, SP_CharacterAppearancesRequests, UserID);
}

void FMMOARPGGateRobot::RunLoginToDSServerRequest()
{
	// it will connect to DS Server, and DS Server will register character in online list.
	int32 UserID = 1;
	int32 SlotPos = 2;
	SIMPLE_CLIENT_SEND(GateClient, SP_LoginToDSServerRequests, UserID, SlotPos);
}
