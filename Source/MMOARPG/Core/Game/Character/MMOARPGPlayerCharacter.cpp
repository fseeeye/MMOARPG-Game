// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerCharacter.h"

#include "../../../MMOARPGMacro.h"
#include "../../Common/MMOARPGGameInstance.h"
#include "../MMOARPGGameMode.h"

// Plugins
#include "ThreadManage.h"


void AMMOARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitKneadingLocation(GetMesh()->GetComponentLocation());

	// Request update KneadingFace Data on Server
	if (GetLocalRole() == ROLE_AutonomousProxy) // primary client
	{
#if !MMOARPG_DEBUG_DS
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
