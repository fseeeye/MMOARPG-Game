// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_Attack.h"

#include "Hit/AbilityHitCollisionBox.h"
#include "Hit/AbilityHitCollisionCapsule.h"
#include "Hit/AbilityHitCollisionSphere.h"
#include "Hit/AbilityHitCollisionCustom.h"

#include <GameFramework/Character.h>

UAnimNotify_Attack::UAnimNotify_Attack()
	: Super()
{
	HitObjectClass = AAbilityHitCollisionBox::StaticClass();
	HitObjectLifeSpan = 4.f;
	HitObjectBindSocketName = TEXT("attack_hit");

	BoxExtent = FVector(32.f);
	SphereRadius = 32.f;
	CapsuleHalfHeight = 44.f;
	CapsuleRadius = 22.f;

	bBox = true;
	bCapsule = false;
	bCustom = false;
	bSphere = false;
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AActor* OuterActor = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(HitObjectBindSocketName);
		FRotator SocketRotation = MeshComp->GetSocketRotation(HitObjectBindSocketName);

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = Cast<APawn>(OuterActor);

		// Span Hit Collision
		if (AAbilityHitCollision* NewHitCollision = OuterActor->GetWorld()->SpawnActor<AAbilityHitCollision>(HitObjectClass, SocketLocation, SocketRotation, ActorSpawnParameters))
		{
			// Set Hit Collision properties 
			NewHitCollision->SetLifeSpan(HitObjectLifeSpan);

			if (NewHitCollision->GetHitComponent())
			{
				FVector HitComponentRelativeLocation = NewHitCollision->GetHitComponent()->GetRelativeLocation();
				NewHitCollision->SetHitComponentRelativeLocation(HitComponentRelativeLocation + HitObjectRelativeOffset);
			}

			if (AAbilityHitCollisionBox* HitBox = Cast<AAbilityHitCollisionBox>(NewHitCollision))
			{
				HitBox->SetBoxExtent(BoxExtent);
			}
			else if (AAbilityHitCollisionCapsule* HitCapsule = Cast<AAbilityHitCollisionCapsule>(NewHitCollision))
			{
				HitCapsule->SetCapsuleHalfHeight(CapsuleRadius);
				HitCapsule->SetCapsuleRadius(CapsuleRadius);
			}
			else if (AAbilityHitCollisionSphere* HitSphere = Cast<AAbilityHitCollisionSphere>(NewHitCollision))
			{
				HitSphere->SetSphereRadius(SphereRadius);
			}
			else if (AAbilityHitCollisionCustom* HitCustom = Cast<AAbilityHitCollisionCustom>(NewHitCollision))
			{

			}
		}
	}
}

#if WITH_EDITOR
void UAnimNotify_Attack::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().ToString() == TEXT("HitObjectClass"))
	{
		if (HitObjectClass.GetDefaultObject()->IsA(AAbilityHitCollisionBox::StaticClass()))
		{
			bBox = true;
			bCapsule = false;
			bCustom = false;
			bSphere = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AAbilityHitCollisionCapsule::StaticClass()))
		{
			bCapsule = true;
			bBox = false;
			bCustom = false;
			bSphere = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AAbilityHitCollisionSphere::StaticClass()))
		{
			bSphere = true;
			bBox = false;
			bCapsule = false;
			bCustom = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AAbilityHitCollisionCustom::StaticClass()))
		{
			bCustom = true;
			bBox = false;
			bCapsule = false;
			bSphere = false;
		}
	}
}
#endif
