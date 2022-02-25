#pragma once

#include "CoreMinimal.h"

// Plugins
//#include "SimpleNetChannelType.h"
#include "SimpleNetManage.h"
//#include "Channel/SimpleChannel.h"


class FMMOARPGGateRobot
{
public:
	FMMOARPGGateRobot();
	~FMMOARPGGateRobot();

	void Init(const FString& InHost, const int32 InPort);

	void NativeTick(float DeltaTime);

public:
	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);

	void Run();

private:
	FSimpleNetManage* GateClient;
};