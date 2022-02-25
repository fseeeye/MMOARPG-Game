#include "MMOARPGTestRobot.h"


FMMOARPGTestRobot::FMMOARPGTestRobot()
{

}

void FMMOARPGTestRobot::InitGate(const FString& InHost, const int32 InPort)
{
	GateRobot.Init(InHost, InPort);
}

void FMMOARPGTestRobot::InitDs(const FString& InHost, const int32 InPort)
{
	DsRobot.Init(InHost, InPort);
}

void FMMOARPGTestRobot::NativeTick(float DeltaTime)
{
	GateRobot.NativeTick(DeltaTime);
	DsRobot.NativeTick(DeltaTime);
}

void FMMOARPGTestRobot::Run()
{
	GateRobot.Run();
	//DsRobot.Run();
}
