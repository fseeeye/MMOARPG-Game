#include "Hit/AbilityHitCollisionSphere.h"

#include <Components/SphereComponent.h>

AAbilityHitCollisionSphere::AAbilityHitCollisionSphere()
{
	HitSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
}

void AAbilityHitCollisionSphere::BeginPlay()
{
	Super::BeginPlay();

}

void AAbilityHitCollisionSphere::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

UPrimitiveComponent* AAbilityHitCollisionSphere::GetHitComponent()
{
	return HitSphereComponent;
}
