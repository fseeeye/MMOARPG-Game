// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGGameInstance.h"

#include <Global/SimpleNetGlobalInfo.h>
#include <ThreadManage.h>
#include <SimpleAdvancedAnimationBPLibrary.h>

void UMMOARPGGameInstance::Init()
{
	Super::Init();
}

void UMMOARPGGameInstance::Tick(float DeltaTime)
{
	if (NetClient)
	{
		NetClient->Tick(DeltaTime);
	}

	GThread::Get()->Tick(DeltaTime);
}

TStatId UMMOARPGGameInstance::GetStatId() const
{
	return TStatId();
}

void UMMOARPGGameInstance::Shutdown()
{
	Super::Shutdown();

	// Free Net Client
	if (NetClient)
	{
		FSimpleNetManage::Destroy(NetClient);
	}

	// Free Thread
	GThread::Destroy();

	// Free AdvancedAnimSystem
	USimpleAdvancedAnimationBPLibrary::DestroyAdvancedAnimSystem();
}

// Create Net Client
void UMMOARPGGameInstance::CreateNetClient()
{
	if (!NetClient)
	{
		// Init Net Channel
		FSimpleNetGlobalInfo::Get()->Init();
		// Create Game Net Client Instance
		NetClient = FSimpleNetManage::CreateManage(ESimpleNetLinkState::LINKSTATE_CONNET, ESimpleSocketType::SIMPLESOCKETTYPE_TCP);
	}
}

// Init Net Client & Connect to Server
void UMMOARPGGameInstance::LinkServer()
{
	if (NetClient)
	{
		if (!NetClient->Init())
		{
			delete NetClient;
			NetClient = nullptr;
		}
	}
}

void UMMOARPGGameInstance::LinkServer(const FSimpleAddr& InAddr)
{
	if (NetClient)
	{
		if (!NetClient->Init(InAddr))
		{
			delete NetClient;
			NetClient = NULL;
		}
	}
}

void UMMOARPGGameInstance::LinkServer(const TCHAR* InIP, uint32 InPort)
{
	if (NetClient)
	{
		if (!NetClient->Init(InIP, InPort))
		{
			delete NetClient;
			NetClient = NULL;
		}
	}
}
