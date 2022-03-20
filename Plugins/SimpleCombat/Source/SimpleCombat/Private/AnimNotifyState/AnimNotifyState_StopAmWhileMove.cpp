// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_StopAmWhileMove.h"

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

void UAnimNotifyState_StopAmWhileMove::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

}

void UAnimNotifyState_StopAmWhileMove::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	// Stop animation playing when detect movement
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (Character->GetCharacterMovement()->Velocity.Size() >= 5.f)
		{
			Character->StopAnimMontage();
		}
	}
}

void UAnimNotifyState_StopAmWhileMove::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

}
