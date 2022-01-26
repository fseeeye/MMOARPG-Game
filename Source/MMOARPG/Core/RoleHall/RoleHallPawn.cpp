// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallPawn.h"

#include "Character/RoleHallCharacterStage.h"

// Sets default values
ARoleHallPawn::ARoleHallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoleHallCharacterStage = nullptr;

	// tips: C++ Pawn need to create Root Component manually to move this pawn.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void ARoleHallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoleHallPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (RoleHallCharacterStage)
	{
		RoleHallCharacterStage->Destroy();
	}
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

