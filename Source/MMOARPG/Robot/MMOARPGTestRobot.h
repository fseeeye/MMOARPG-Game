#pragma once

#include "CoreMinimal.h"

#include "MMOARPGGateRobot.h"
#include "MMOARPGDsRobot.h"

// Plugins
#include "SimpleNetManage.h"
#include "MMOARPGCommType.h"


class FMMOARPGTestRobot
{
public:
	FMMOARPGTestRobot();

	void InitGate(const FString& InHost, const int32 InPort);
	void InitDs(const FString& InHost, const int32 InPort);

	void NativeTick(float DeltaTime);

	void Run();

public:
	FORCEINLINE FMMOARPGGateRobot& GetGateRobot() { return GateRobot; }
	FORCEINLINE FMMOARPGDsRobot& GetDsRobot() { return DsRobot; }

private:
	FMMOARPGGateRobot GateRobot;
	FMMOARPGDsRobot DsRobot;

	FMMOARPGUserData UserData;
};
