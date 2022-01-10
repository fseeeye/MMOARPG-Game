// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGGameInstance.h"

#include "Global/SimpleNetGlobalInfo.h"
#include "ThreadManage.h"

void UMMOARPGGameInstance::Init()
{
	Super::Init();
}

void UMMOARPGGameInstance::Tick(float DeltaTime)
{
	if (NetClient)
	{
		NetClient->Tick(DeltaTime);
		GThread::Get()->Tick(DeltaTime);
	}
}

TStatId UMMOARPGGameInstance::GetStatId() const
{
	return TStatId();
}

void UMMOARPGGameInstance::Shutdown()
{
	Super::Shutdown();

	if (NetClient)
	{
		FSimpleNetManage::Destroy(NetClient);
		GThread::Destroy();
	}
}

// Create Net Client
void UMMOARPGGameInstance::CreateNetClient()
{
	// Init Net Channel
	FSimpleNetGlobalInfo::Get()->Init();
	// Create Game Net Client Instance
	NetClient = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_TCP);
}

// Init Net Client & Connect to Server
void UMMOARPGGameInstance::LinkServer()
{
	if (NetClient)
	{
		if (!NetClient->Init())
		{
			delete NetClient;
			NetClient = NULL;
		}
	}
}
