#include "Core/Features/SimpleFootIK.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/KismetSystemLibrary.h>


FSimpleFootIK::FSimpleFootIK()
	: Character(nullptr), bPendingKill(false), TraceDistance(50.f), TraceStart(50.f), InterpSpeed(18.f)
{
}

void FSimpleFootIK::Init(ACharacter* InCharacter, const TArray<FName> InBoneNames, float InTraceDistance /*= 50.f*/, float InTraceStart /*= 50.f*/, float InInterpSpeed /*= 18.f*/)
{
	Character = InCharacter;
	TraceDistance = InTraceDistance;
	InInterpSpeed = InInterpSpeed;

	for (auto& BoneName : InBoneNames)
	{
		IKInfos.Add(BoneName, FFootIKInfo());
	}
}

void FSimpleFootIK::InnerTick(float InDeltaTime)
{
	for (auto& IKInfo : IKInfos)
	{
		float OffsetTarget = FootTrace(IKInfo.Key, TraceDistance);
		// Interp change foot offset movement.
		IKInfo.Value.Offset = FMath::FInterpTo(IKInfo.Value.Offset, OffsetTarget, InDeltaTime, InterpSpeed);
	}
}

float FSimpleFootIK::GetOffset(const FName& InBoneName)
{
	if (FFootIKInfo* TargetIKInfo = GetInfo(InBoneName))
	{
		return TargetIKInfo->Offset;
	}

	return 0.f;
}

float FSimpleFootIK::FootTrace(const FName& InBoneName, float InTraceDistance)
{
	if (Character)
	{
		if (Character->IsPendingKill())
		{
			bPendingKill = true;
			Character = nullptr;
			return 0.f;
		}

		FVector BoneLocation = Character->GetMesh()->GetSocketLocation(InBoneName);
		float CharacterLocationZ = Character->GetActorLocation().Z;
		float CapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// Calculate ray start & end location
		FVector RayStartLocation = BoneLocation + FVector(0.f, 0.f, TraceStart);
		FVector RayEndLocation = FVector(
			RayStartLocation.X, 
			RayStartLocation.Y, 
			CharacterLocationZ - (CapsuleHalfHeight + InTraceDistance)
		);

		// Trace ray
		FHitResult RayHitResult;
		TArray<AActor*> Ignores;
		if (UKismetSystemLibrary::LineTraceSingle(
				Character->GetWorld(),
				RayStartLocation,
				RayEndLocation,
				TraceTypeQuery1,
				false,
				Ignores,
				//EDrawDebugTrace::ForOneFrame, // only for debug
				EDrawDebugTrace::None,
				RayHitResult,
				true)
			)
		{
			return (RayHitResult.Location - RayHitResult.TraceEnd).Size() - InTraceDistance; // return hit offset
		}
	}

	return 0.f;
}
