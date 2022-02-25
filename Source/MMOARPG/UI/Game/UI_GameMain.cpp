// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMain.h"

// Plugins
#include "ThreadManage.h"

#define LOCTEXT_NAMESPACE "UI_GameMain"

void UUI_GameMain::NativeConstruct()
{
	Super::NativeConstruct();
	
	// TMP
	Robot.InitGate("127.0.0.1", 11222);
}

void UUI_GameMain::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUI_GameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// TMP
	Robot.NativeTick(InDeltaTime);

	GThread::Get()->GetCoroutines().BindLambda(0.5f, [&]()
	{	
		Robot.Run();
	});

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
