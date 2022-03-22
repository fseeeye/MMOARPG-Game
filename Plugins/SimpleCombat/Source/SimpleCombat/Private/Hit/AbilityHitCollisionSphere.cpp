#include "Hit/AbilityHitCollisionSphere.h"

#include <Components/SphereComponent.h>

AAbilityHitCollisionSphere::AAbilityHitCollisionSphere()
	: Super()
{
	InitializeDefaults();
}

AAbilityHitCollisionSphere::AAbilityHitCollisionSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitializeDefaults();
}

void AAbilityHitCollisionSphere::InitializeDefaults()
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
