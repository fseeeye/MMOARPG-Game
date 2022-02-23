// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGPlayerAnimInstance.h"
#include "../../../Common/Interface/KneadingInterface.h"

void UMMOARPGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Update KeadingFace data
	if (IKneadingInterface* KneadingInterface = Cast<IKneadingInterface>(TryGetPawnOwner()))
	{
		LegSize = KneadingInterface->GetLegSize();
		WaistSize = KneadingInterface->GetWaistSize();
		ArmSize = KneadingInterface->GetArmSize();
		// ...
	}


}
