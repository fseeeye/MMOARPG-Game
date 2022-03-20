// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_BlockMoveInput.h"

#include <GameFramework/Character.h>

void UAnimNotifyState_BlockMoveInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Ignore movement input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if ((Character->GetWorld()->IsNetMode(ENetMode::NM_Client) && Character->GetLocalRole() == ROLE_AutonomousProxy)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_Standalone)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			Character->GetController()->SetIgnoreMoveInput(true);
		}
	}
}

void UAnimNotifyState_BlockMoveInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_BlockMoveInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// Resume movement input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if ((Character->GetWorld()->IsNetMode(ENetMode::NM_Client) && Character->GetLocalRole() == ROLE_AutonomousProxy)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_Standalone)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			Character->GetController()->SetIgnoreMoveInput(false);
		}
	}
}
