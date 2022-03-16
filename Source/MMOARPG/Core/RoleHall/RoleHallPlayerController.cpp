// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallPlayerController.h"

ARoleHallPlayerController::ARoleHallPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true; // adapt to mobile platform
}

void ARoleHallPlayerController::Zoom(float InDeltaMovement)
{
	if (InDeltaMovement > 0)
	{
		SimpleZoom.ZoomPositive(InDeltaMovement * 10.f);
	}
	else if (InDeltaMovement < 0)
	{
		SimpleZoom.ZoomNegative(InDeltaMovement * 10.f);
	}
}

void ARoleHallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Init Character Rotator & Zoomer
	SimpleRotate.Register(this, NULL);
	SimpleZoom.Register(GetPawn(), 200.f);
	SimplePanelMove.Register(this, GetPawn(), 100.f);
}

void ARoleHallPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoleHallPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// add mouse left released input binding
	InputComponent->BindAction("MouseLeftButton", IE_Released, this, &ARoleHallPlayerController::StopRotateCharacter);
	// add mouse wheel input binding
	InputComponent->BindAxis("MouseWheelNew", this, &ARoleHallPlayerController::Zoom);
	// add mouse right released input binding
	InputComponent->BindAction("MouseRightButton", IE_Pressed, this, &ARoleHallPlayerController::StartMove);
	InputComponent->BindAction("MouseRightButton", IE_Released, this, &ARoleHallPlayerController::StopMove);
}
