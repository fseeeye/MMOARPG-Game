#include "MMOARPGHitCollisionBox.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags.h"
#include "../../Character/MMOARPGCharacterBase.h"

AMMOARPGHitCollisionBox::AMMOARPGHitCollisionBox()
	: Super()
{
	InitializeDefaults();
}

AMMOARPGHitCollisionBox::AMMOARPGHitCollisionBox(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitializeDefaults();
}

void AMMOARPGHitCollisionBox::InitializeDefaults()
{

}

void AMMOARPGHitCollisionBox::BeginPlay()
{
	Super::BeginPlay();

}

void AMMOARPGHitCollisionBox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AMMOARPGHitCollisionBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HandleDamage(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (GetInstigator() != OtherActor) // overlap actor isn't ourself
	{
		if (OtherActor->IsA(AMMOARPGCharacterBase::StaticClass()))
		{
			// Init and Send Gameplay Event
			FGameplayEventData EventData;
			EventData.Instigator = GetInstigator();
			EventData.Target = OtherActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), FGameplayTag::RequestGameplayTag(TEXT("Player.Attack.ComboAttack")), EventData); // TODO: EventTag
		}
	}
}

