// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerCharacter.h"

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
		//if (UMMOARPGGameInstance* GameInstance = GetWorld()->GetGameInstance<UMMOARPGGameInstance>())
		//{
		//	UpdateKneadingDataOnServer(GameInstance->GetUserData().ID); // RPC
		//}

		// TMP: only for test
		GThread::Get()->GetCoroutines().BindLambda(0.7f, [&]()
		{
			if (UMMOARPGGameInstance* GameInstance = GetWorld()->GetGameInstance<UMMOARPGGameInstance>())
			{
				UpdateKneadingDataOnServer(1); // RPC
			}
		});
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
