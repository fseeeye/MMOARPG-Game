// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// Plugins
#include "SimpleNetChannelType.h"
#include "MMOARPGCommType.h"

#include "MMOARPGGameMode.generated.h"

class FSimpleChannel;

UCLASS(minimalapi)
class AMMOARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMMOARPGGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController. */
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	// Get Kneading Data from Center Server
	void UpdateKneadingDataRequest(int32 InUserID);
	
	// Get Gamepaly Data from Center Server (include: Gameplay Attributes)
	void GetCharacterGameplayDataRequest(int32 InUserID, int32 InCharacterID);

private:
	void BindNetClientRcv();

	void LinkServer();

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);

	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

private:
	FDelegateHandle RecvDelegate;
};
