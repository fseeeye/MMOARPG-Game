#include "Hit/AbilityHitCollisionSphere.h"

#include <Components/SphereComponent.h>

AAbilityHitCollisionSphere::AAbilityHitCollisionSphere()
	: Super()
{
	HitSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	HitSphereComponent->SetupAttachment(RootComponent); // attach to root component
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

void AAbilityHitCollisionSphere::SetSphereRadius(float InNewRadius)
{
	HitSphereComponent->SetSphereRadius(InNewRadius);
}
