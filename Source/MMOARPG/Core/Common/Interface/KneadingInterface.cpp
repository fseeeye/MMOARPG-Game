// Fill out your copyright notice in the Description page of Project Settings.


#include "KneadingInterface.h"

// Add default functionality here for any IKneadingInterface functions that are not pure virtual.

IKneadingInterface::IKneadingInterface()
	: LegSize(0.f), WaistSize(0.f), ArmSize(0.f)
{
}

void IKneadingInterface::ResetMeshPosition(USceneComponent* InMesh)
{
	if (InMesh)
	{
		FVector ComponentLocation = Location;
		ComponentLocation.Z += LegSize;
		InMesh->SetWorldLocation(ComponentLocation);
	}
}
