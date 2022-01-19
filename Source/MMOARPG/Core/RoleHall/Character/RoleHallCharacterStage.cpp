// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallCharacterStage.h"

// Sets default values
ARoleHallCharacterStage::ARoleHallCharacterStage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleHallCharacterStage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleHallCharacterStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoleHallCharacterStage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

