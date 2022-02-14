// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SimpleNetManage.h"
#include "MMOARPGCommType.h"
#include "Protocol/LoginProtocol.h" // Plugin: MMOARPGComm

#include "MMOARPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UMMOARPGGameInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

	virtual TStatId GetStatId() const;

	virtual void Shutdown();

public:
	void CreateNetClient();

	void LinkServer();
	void LinkServer(const FSimpleAddr& InAddr);

	FORCEINLINE FSimpleNetManage* GetNetClient() { return NetClient; }
	FORCEINLINE FMMOARPGUserData& GetUserData() { return UserData; }
	FORCEINLINE FMMOARPGGateStatus& GetGateStatus() { return GateStatus; }

private:
	FSimpleNetManage* NetClient;
	FMMOARPGUserData UserData;
	FMMOARPGGateStatus GateStatus;
};
