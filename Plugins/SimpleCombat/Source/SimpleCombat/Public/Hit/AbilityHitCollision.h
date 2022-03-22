#pragma once

#include "CoreMinimal.h"
#include "AbilityHitCollision.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AAbilityHitCollision : public AActor
{
	GENERATED_BODY()

	/** As RootComponent: The component that defines the transform (location, rotation, scale) of this Actor in the world, all other components must be attached to this one somehow */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HitCollisionRootComponent;

public:
	AAbilityHitCollision();

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;

	/**
	 *	Function called every frame on this Actor. Override this function to implement custom logic to be executed every frame.
	 *	Note that Tick is disabled by default, and you will need to check PrimaryActorTick.bCanEverTick is set to true to enable it.
	 *
	 *	@param	DeltaSeconds	Game time elapsed during last frame modified by the time dilation
	 */
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

	virtual UPrimitiveComponent* GetHitComponent() { return nullptr; }

	void SetHitComponentRelativeLocation(const FVector& InNewRelativeLocation);
};
