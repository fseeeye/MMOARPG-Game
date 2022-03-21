#include "Hit/AbilityHitCollisionBox.h"

#include <Components/BoxComponent.h>

AAbilityHitCollisionBox::AAbilityHitCollisionBox()
{
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
}

void AAbilityHitCollisionBox::BeginPlay()
{
	Super::BeginPlay();

}

void AAbilityHitCollisionBox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

UPrimitiveComponent* AAbilityHitCollisionBox::GetHitComponent()
{
	return HitBoxComponent;
}
