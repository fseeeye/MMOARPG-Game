// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMain.h"

#if MMOARPG_DEBUG_DS 
#include "../../Core/Game/Character/MMOARPGPlayerCharacter.h"
#endif

// Plugins
#include "ThreadManage.h"

#define LOCTEXT_NAMESPACE "UI_GameMain"

void UUI_GameMain::NativeConstruct()
{
	Super::NativeConstruct();
	
#if MMOARPG_DEBUG_DS 
	if (AMMOARPGPlayerCharacter* PlayerCharacter = GetPawn<AMMOARPGPlayerCharacter>())
	{
		Robot.GetGateRobot().StartDelegate.BindUObject(PlayerCharacter, &AMMOARPGPlayerCharacter::UpdateKneadingDataOnServer_Debug);
	}

	//UpdateKneadingDataOnServer_Debug
	Robot.InitGate("127.0.0.1", 11222);
#endif
}

void UUI_GameMain::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUI_GameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

#if MMOARPG_DEBUG_DS
	Robot.NativeTick(InDeltaTime);
#endif
}

void UUI_GameMain::RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel)
{
	//switch (ProtocolNumber)
	//{
	//	default:
	//		break;
	//}
}

void UUI_GameMain::LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg)
{
	if (InType == ESimpleNetErrorType::HAND_SHAKE_SUCCESS)
	{
		
	}
}

#undef LOCTEXT_NAMESPACE
