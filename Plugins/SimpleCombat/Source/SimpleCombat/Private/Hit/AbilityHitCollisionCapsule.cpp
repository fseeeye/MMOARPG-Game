#include "Hit/AbilityHitCollisionCapsule.h"

#include <Components/CapsuleComponent.h>

AAbilityHitCollisionCapsule::AAbilityHitCollisionCapsule()
{
	HitCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
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
