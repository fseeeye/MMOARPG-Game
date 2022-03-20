// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_BlockInput.h"

#include <GameFramework/Character.h>

void UAnimNotifyState_BlockInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Block controller input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if ((Character->GetWorld()->IsNetMode(ENetMode::NM_Client) && Character->GetLocalRole() == ROLE_AutonomousProxy)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_Standalone)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			Character->DisableInput(Character->GetWorld()->GetFirstPlayerController());
		}
	}
}

void UAnimNotifyState_BlockInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_BlockInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// Resume controller input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if ((Character->GetWorld()->IsNetMode(ENetMode::NM_Client) && Character->GetLocalRole() == ROLE_AutonomousProxy)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_Standalone)
			|| Character->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			Character->EnableInput(Character->GetWorld()->GetFirstPlayerController());
		}
	}
}
