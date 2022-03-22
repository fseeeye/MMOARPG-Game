#include "Hit/AbilityHitCollisionCapsule.h"

#include <Components/CapsuleComponent.h>

AAbilityHitCollisionCapsule::AAbilityHitCollisionCapsule()
	: Super()
{
	HitCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCapsuleComponent->SetupAttachment(RootComponent); // attach to root component
}

void AAbilityHitCollisionCapsule::BeginPlay()
{
	Super::BeginPlay();

}

void AAbilityHitCollisionCapsule::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

UPrimitiveComponent* AAbilityHitCollisionCapsule::GetHitComponent()
{
	return HitCapsuleComponent;
}

void AAbilityHitCollisionCapsule::SetCapsuleHalfHeight(float InNewHalfHeight)
{
	HitCapsuleComponent->SetCapsuleHalfHeight(InNewHalfHeight);
}

void AAbilityHitCollisionCapsule::SetCapsuleRadius(float InNewRadius)
{
	HitCapsuleComponent->SetCapsuleRadius(InNewRadius);
}
