#pragma once

#include "CoreMinimal.h"
#include "SimpleAdvancedAnimationType.h"

#include <GameFramework/Character.h>


struct FSimpleFootIK
{
public:
	FSimpleFootIK();

	void Init(ACharacter* InCharacter, const TArray<FName> InBoneNames, float InTraceDistance = 50.f, float InTraceStart = 50.f, float InInterpSpeed = 18.f);

	void InnerTick(float InDeltaTime);

public:
	FORCEINLINE FFootIKInfo* GetInfo(const FName& InBoneName) { return IKInfos.Find(InBoneName); }
	float GetOffset(const FName& InBoneName);
	FORCEINLINE bool IsCharacterPendingKill() { return bPendingKill; }

protected:
	// Emit a ray to floor to detect distance
	float FootTrace(const FName& InBoneName, float InTraceDistance);

protected:
	ACharacter* Character;
	bool bPendingKill;

	TMap<FName, FFootIKInfo> IKInfos;
	float TraceDistance;
	float TraceStart;
	float InterpSpeed;
};