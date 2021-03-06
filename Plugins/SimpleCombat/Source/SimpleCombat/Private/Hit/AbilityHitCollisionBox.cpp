#include "Hit/AbilityHitCollisionBox.h"

#include <Components/BoxComponent.h>

AAbilityHitCollisionBox::AAbilityHitCollisionBox()
	: Super()
{
	InitializeDefaults();
}

AAbilityHitCollisionBox::AAbilityHitCollisionBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitializeDefaults();
}

void AAbilityHitCollisionBox::InitializeDefaults()
{
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBoxComponent->SetupAttachment(RootComponent); // attach to root component
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

void AAbilityHitCollisionBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitBoxComponent->SetBoxExtent(InNewBoxExtent);
}
