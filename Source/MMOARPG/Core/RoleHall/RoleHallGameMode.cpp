// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallGameMode.h"

#include "RoleHallHUD.h"
#include "RoleHallPawn.h"
#include "RoleHallPlayerController.h"

ARoleHallGameMode::ARoleHallGameMode()
{
	// Register HUD
	HUDClass = ARoleHallHUD::StaticClass();
	// Register Pawn
	DefaultPawnClass = ARoleHallPawn::StaticClass();
	// Register PlayerController
	PlayerControllerClass = ARoleHallPlayerController::StaticClass();
}
