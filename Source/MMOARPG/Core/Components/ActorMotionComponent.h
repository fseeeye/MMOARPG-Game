// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorMotionComponent.generated.h"

class AMMOARPGCharacterBase;
class UCharacterMovementComponent;
class UCapsuleComponent;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMOARPG_API UActorMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorMotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void LockView(float DeltaTime, bool bClearPitch = false);

	void ResetRotationRate(float DeltaTime);

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
	bool bFast;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	FVector2D RotationRate;
};
