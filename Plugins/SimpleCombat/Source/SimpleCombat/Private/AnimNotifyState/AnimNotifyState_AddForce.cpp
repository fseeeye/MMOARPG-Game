// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_AddForce.h"

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

UAnimNotifyState_AddForce::UAnimNotifyState_AddForce()
	: Super()
	, ForceDirection(1.f, 0.f, 0.f)
	, ForceSize(600000.f)
	, TotalDurationTime(0.f)
{

}

void UAnimNotifyState_AddForce::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	TotalDurationTime = TotalDuration;
	ForceConsuming = ForceSize;
}

void UAnimNotifyState_AddForce::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (TotalDurationTime > 0.f)
	{
		if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
		{
			FVector ActorForceVector = CalcForceDirectionInCharacterSpace(Character);
			Character->GetCharacterMovement()->AddForce(ForceConsuming * ActorForceVector);
			// Force decay per frame
			if (ForceConsuming > 0.f)
				ForceConsuming -= ForceConsuming / (TotalDurationTime * (1.f / FrameDeltaTime));
		}
	}
}

void UAnimNotifyState_AddForce::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}

FVector UAnimNotifyState_AddForce::CalcForceDirectionInCharacterSpace(ACharacter* InCharacter)
{
	if (InCharacter)
	{
		if (ForceDirection.X != 0.f)
		{
			return InCharacter->GetActorForwardVector() * ForceDirection.X;
		}
		else if (ForceDirection.Y != 0.f)
		{
			return InCharacter->GetActorRightVector() * ForceDirection.Y;
		}
		else if (ForceDirection.Z != 0.f)
		{
			return InCharacter->GetActorUpVector() * ForceDirection.Z;
		}
	}

	return FVector::ZeroVector;
}
