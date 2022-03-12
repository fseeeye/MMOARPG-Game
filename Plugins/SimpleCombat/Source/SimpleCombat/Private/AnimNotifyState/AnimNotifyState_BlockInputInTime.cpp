// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_BlockInputInTime.h"

#include <GameFramework/Character.h>

void UAnimNotifyState_BlockInputInTime::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Ignore movement input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (Character->GetController())
		{
			Character->GetController()->SetIgnoreMoveInput(true);
		}
	}
}

void UAnimNotifyState_BlockInputInTime::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_BlockInputInTime::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// Resume movement input
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (Character->GetController())
		{
			Character->GetController()->SetIgnoreMoveInput(false);
		}
	}
}
