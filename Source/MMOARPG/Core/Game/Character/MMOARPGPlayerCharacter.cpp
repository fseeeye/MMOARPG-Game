// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerCharacter.h"

#include "../../../MMOARPGMacro.h"
#include "../../Common/MMOARPGGameInstance.h"
#include "../MMOARPGGameMode.h"
#include "../MMOARPGPlayerState.h"

// Plugins
#include "ThreadManage.h"


void AMMOARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitKneadingLocation(GetMesh()->GetComponentLocation());

	if (GetLocalRole() == ROLE_AutonomousProxy) // primary client
	{
		// use CA in Player State to update
		if (AMMOARPGPlayerState* MMOARPGPlayerState = GetPlayerState<AMMOARPGPlayerState>())
		{
			UpdateKneadingModelAttributes(MMOARPGPlayerState->GetCA());
		}
		
#if !MMOARPG_DEBUG_DS
		// Request update KneadingFace Data on Server
		UpdateKneadingDataOnServer_Debug();
#endif
	}
	else if (GetLocalRole() == ROLE_SimulatedProxy) // other client
	{
	}
}

void AMMOARPGPlayerCharacter::UpdateKneadingDataOnServer_Implementation(int32 InUserID)
{
	if (AMMOARPGGameMode* GameMode = GetWorld()->GetAuthGameMode<AMMOARPGGameMode>())
	{
		UserID = InUserID;
		GameMode->UpdateKneadingDataRequest(InUserID);
	}
}

void AMMOARPGPlayerCharacter::UpdateKneadingDataOnClient_Implementation(const FMMOARPGCharacterAppearance& InCA)
{
	UpdateKneadingModelAttributes(InCA);

	if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		// save CA in client Player State
		if (AMMOARPGPlayerState* MMOARPGPlayerState = GetPlayerState<AMMOARPGPlayerState>())
		{
			MMOARPGPlayerState->GetCA() = InCA;
		}
	}
}

void AMMOARPGPlayerCharacter::UpdateKneadingDataOnServer_Debug()
{
	if (UMMOARPGGameInstance* GameInstance = GetWorld()->GetGameInstance<UMMOARPGGameInstance>())
	{
#if MMOARPG_DEBUG_DS
		UpdateKneadingDataOnServer(1); // TMP: only for test
#else
		UpdateKneadingDataOnServer(GameInstance->GetUserData().ID); // RPC
#endif
	}
}

void AMMOARPGPlayerCharacter::UpdateKneadingModelAttributes()
{

}

void AMMOARPGPlayerCharacter::UpdateKneadingModelAttributes(const FMMOARPGCharacterAppearance& InCA)
{
	SetLegSize(InCA.LegSize);
	SetWaistSize(InCA.WaistSize);
	SetArmSize(InCA.ArmSize);

	// 调整 mesh 位置，防止腿部进入地面
	ResetMeshPosition(GetMesh());
}
