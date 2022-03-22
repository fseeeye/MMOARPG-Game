#pragma once

#include "CoreMinimal.h"
#include "AbilityHitCollision.h"
#include "AbilityHitCollisionCapsule.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AAbilityHitCollisionCapsule : public AAbilityHitCollision
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* HitCapsuleComponent;

public:
	AAbilityHitCollisionCapsule();

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
	virtual UPrimitiveComponent* GetHitComponent() override;

	void SetCapsuleHalfHeight(float InNewHalfHeight);
	void SetCapsuleRadius(float InNewRadius);
};
