// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../MMOARPGGameType.h"

#include "FlyComponent.generated.h"


class AMMOARPGCharacterBase;
class UCharacterMovementComponent;
class UCapsuleComponent;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOARPG_API UFlyComponent : public UActorComponent
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

protected:
	UPROPERTY()
	TWeakObjectPtr<AMMOARPGCharacterBase> Owner_CharacterBase;

	UPROPERTY()
	TWeakObjectPtr<UCharacterMovementComponent> Owner_MovementComponent;

	UPROPERTY()
	TWeakObjectPtr<UCapsuleComponent> Owner_CapsuleComponent;

	UPROPERTY()
	TWeakObjectPtr<UCameraComponent> Owner_CameraComponent;

	UPROPERTY()
	FRotator LastRotation;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	FVector2D FlyRotationRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	EFlyDodgeState FlyDodgeState;

	FTimeBool bFastFly;

	FTimeBool bLanded;
};
