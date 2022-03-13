// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMotionComponent.h"

#include "../../MMOARPGGameType.h"

#include "FlyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOARPG_API UFlyComponent : public UActorMotionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void DebugPrint(float InDeltaTime, const FString& InMsg);

public:
	void ResetFly();
	void ResetFlyToWalking();

	// Called for flying forwards/backward input
	void FlyForwardAxis(float InAxisValue);

	// Switch `bFastFly` value
	void SwitchFastFly();

	// Switch Dodge state
	void SwitchDodge(EFlyDodgeState InTargetDodge);

	// Call for flying landed
	UFUNCTION()
	void OnHitLand(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	EFlyDodgeState FlyDodgeState;

	bool bFastFly;
	
	FTimeBool bDodgeFly;

	FTimeBool bLanded;
};
