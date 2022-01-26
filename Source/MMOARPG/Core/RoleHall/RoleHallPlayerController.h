// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Plugins
#include "Core/SimpleRotate.h"
#include "Core/SimpleZoom.h"
#include "Core/SimplePanelMove.h"

#include "RoleHallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API ARoleHallPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARoleHallPlayerController();

	FORCEINLINE void StartRotateCharacter() { SimpleRotate.StartRotating(); }
	FORCEINLINE void StopRotateCharacter() { SimpleRotate.EndRotating(); }
	FORCEINLINE void ResetRotateTarget(AActor* InNewTarget) { SimpleRotate.ResetTargetActor(InNewTarget); }

	FORCEINLINE void StartMove() { SimplePanelMove.StartMove(); }
	FORCEINLINE void StopMove() { SimplePanelMove.EndMove(); }

	void Zoom(float InDeltaMovement);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

private:
	SimpleActorBrowse::FSimpleRotate SimpleRotate;
	SimpleActorBrowse::FSimpleZoom SimpleZoom;
	SimpleActorBrowse::FSimplePanelMove SimplePanelMove;
};
