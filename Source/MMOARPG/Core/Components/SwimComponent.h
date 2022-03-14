// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMotionComponent.h"
#include "SwimComponent.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API USwimComponent : public UActorMotionComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Called for swimming forward input
	void SwimForwardAxis(float InAxisValue);

	// Switch `bFast`
	void SwitchFastSwim();
};
