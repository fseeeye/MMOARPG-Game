// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleHallCharacterStage.h"

#include "../RoleHallPlayerController.h"

// Components
#include "Components/CapsuleComponent.h"


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
	
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnClicked.AddDynamic(this, &ARoleHallCharacterStage::OnCapsuleClicked);
	}
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

void ARoleHallCharacterStage::OnCapsuleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (ARoleHallPlayerController* RoleHallPlayerController = GetWorld()->GetFirstPlayerController<ARoleHallPlayerController>())
	{
		RoleHallPlayerController->ResetRotateTarget(this);
		RoleHallPlayerController->StartRotateCharacter();
	}
}

