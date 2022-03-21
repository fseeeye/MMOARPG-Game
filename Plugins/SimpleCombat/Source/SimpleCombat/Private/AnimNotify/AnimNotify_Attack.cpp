// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_Attack.h"

#include "Hit/AbilityHitCollisionBox.h"
#include <GameFramework/Character.h>

UAnimNotify_Attack::UAnimNotify_Attack()
	: Super()
{
	HitObjectClass = AAbilityHitCollisionBox::StaticClass();
	HitObjectLifeSpan = 4.f;
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(HitObjectBindSocketName);
		FRotator SocketRotation = MeshComp->GetSocketRotation(HitObjectBindSocketName);

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = Cast<APawn>(Character);

		// span hit collision
		if (AAbilityHitCollision* NewHitCollision = Character->GetWorld()->SpawnActor<AAbilityHitCollision>(HitObjectClass, SocketLocation, SocketRotation, ActorSpawnParameters))
		{
			NewHitCollision->SetLifeSpan(HitObjectLifeSpan);
		}
	}
}
