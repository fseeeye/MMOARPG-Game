// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerCharacter.h"

void AMMOARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitKneadingLocation(GetMesh()->GetComponentLocation());
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
