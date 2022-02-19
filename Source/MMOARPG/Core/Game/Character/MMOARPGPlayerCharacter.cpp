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

	// ���� mesh λ�ã���ֹ�Ȳ��������
	ResetMeshPosition(GetMesh());
}
