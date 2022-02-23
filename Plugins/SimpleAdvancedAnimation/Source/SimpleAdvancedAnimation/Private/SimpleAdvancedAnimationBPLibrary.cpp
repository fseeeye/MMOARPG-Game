// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleAdvancedAnimationBPLibrary.h"
#include "SimpleAdvancedAnimation.h"

#include "Core/SimpleAdvancedAnimSystem.h"

USimpleAdvancedAnimationBPLibrary::USimpleAdvancedAnimationBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

//float USimpleAdvancedAnimationBPLibrary::SimpleAdvancedAnimationSampleFunction(float Param)
//{
//	return -1;
//}

int32 USimpleAdvancedAnimationBPLibrary::CreateFootIK(ACharacter* InCharacter, const TArray<FName> InBoneNames, float InTraceDistance /*= 50.f*/, float InTraceStart /*= 50.f*/, float InInterpSpeed /*= 18.f*/)
{
	return FSimpleAdvancedAnimSystem::Get()->CreateFootIK(InCharacter, InBoneNames, InTraceDistance, InTraceStart, InInterpSpeed);
}

FFootIKInfo USimpleAdvancedAnimationBPLibrary::FindFootIKInfo(const int32 InHandle, const FName& InBoneName)
{
	if (FFootIKInfo* IKInfo = FSimpleAdvancedAnimSystem::Get()->FindFootIKInfo(InHandle, InBoneName))
	{
		return *IKInfo;
	}

	return FFootIKInfo();
}

float USimpleAdvancedAnimationBPLibrary::FindFootIKOffset(const int32 InHandle, const FName& InBoneName)
{
	return FSimpleAdvancedAnimSystem::Get()->FindFootIKOffset(InHandle, InBoneName);
}

float USimpleAdvancedAnimationBPLibrary::CalculateFootIKCentroidOffsetZ(const TArray<float>& InOffsets)
{
	float MinOffsetZ = 0.f;
	for (auto& Offset : InOffsets)
	{
		MinOffsetZ = FMath::Min(MinOffsetZ, Offset);
	}

	return MinOffsetZ < 0.f ? MinOffsetZ : 0.f;
}

void USimpleAdvancedAnimationBPLibrary::DestroyAdvancedAnimSystem()
{
	FSimpleAdvancedAnimSystem::Get()->Destory();
}

