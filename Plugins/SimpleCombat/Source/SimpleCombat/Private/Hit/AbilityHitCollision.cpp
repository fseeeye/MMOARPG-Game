#include "Hit/AbilityHitCollision.h"

AAbilityHitCollision::AAbilityHitCollision()
{
	InitialLifeSpan = 4.f;
}

void AAbilityHitCollision::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* HitComponent = GetHitComponent())
	{
		HitComponent->SetHiddenInGame(false); // TMP
		HitComponent->OnComponentBeginOverlap.AddDynamic(this, &AAbilityHitCollision::BeginOverlap); // bind hit callback func
	}
}

void AAbilityHitCollision::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds); // ?

}
