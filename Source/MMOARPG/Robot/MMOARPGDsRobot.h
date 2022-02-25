#pragma once

#include "CoreMinimal.h"

// Plugins
#include "SimpleNetManage.h"


class FMMOARPGDsRobot
{
public:
	FMMOARPGDsRobot();

	void Init(const FString& InHost, const int32 InPort);

	void NativeTick(float DeltaTime);

	void Run();

private:
	FSimpleNetManage* DsClient;
};