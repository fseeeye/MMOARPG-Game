// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"

#include "LoginHUD.h"
#include "LoginPawn.h"
#include "LoginPlayerController.h"

ALoginGameMode::ALoginGameMode()
{
	// Register HUD
	HUDClass = ALoginHUD::StaticClass();
	// Register Pawn
	DefaultPawnClass = ALoginPawn::StaticClass();
	// Register Controller Class
	PlayerControllerClass = ALoginPlayerController::StaticClass();
}
