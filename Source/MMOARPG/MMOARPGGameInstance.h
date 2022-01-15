// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SimpleNetManage.h"
#include "MMOARPGCommType.h"

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

	inline FSimpleNetManage* GetNetClient() { return NetClient; }
	inline FMMOARPGUserData& GetUserData() { return UserData; }

private:
	FSimpleNetManage* NetClient;
	FMMOARPGUserData UserData;
};
