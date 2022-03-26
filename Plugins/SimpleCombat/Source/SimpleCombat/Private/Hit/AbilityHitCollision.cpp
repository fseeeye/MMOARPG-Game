#include "Hit/AbilityHitCollision.h"

AAbilityHitCollision::AAbilityHitCollision()
	: Super()
{
	InitializeDefaults();
}

AAbilityHitCollision::AAbilityHitCollision(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitializeDefaults();
}

void AAbilityHitCollision::InitializeDefaults()
{
	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HitCollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	InitialLifeSpan = 4.f;
}

void AAbilityHitCollision::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* HitComponent = GetHitComponent())
	{
		// HitComponent->SetHiddenInGame(false); // TMP
		HitComponent->OnComponentBeginOverlap.AddDynamic(this, &AAbilityHitCollision::HandleDamage); // bind hit callback func
	}
}

void AAbilityHitCollision::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AAbilityHitCollision::SetHitComponentRelativeLocation(const FVector& InNewRelativeLocation)
{
	if (UPrimitiveComponent* HitComponent = GetHitComponent())
	{
		HitComponent->SetRelativeLocation(InNewRelativeLocation);
	}
}
