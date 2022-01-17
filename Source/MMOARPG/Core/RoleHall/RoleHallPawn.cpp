// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallPawn.h"

// Sets default values
ARoleHallPawn::ARoleHallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleHallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleHallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoleHallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

