#pragma once

#include "CoreMinimal.h"

#include "Core/Features/SimpleFootIK.h"
#include "SimpleAdvancedAnimationType.h"

#include <Tickable.h>
#include <GameFramework/Character.h>


class FSimpleAdvancedAnimSystem : public FTickableGameObject
{
public:
	static FSimpleAdvancedAnimSystem* Get();

	static void Destory();

public:
	/**
	 * It will be called from within LevelTick.cpp after ticking all actors
	 * or from the rendering thread (depending on bIsRenderingThreadObject)
	 *
	 * @param DeltaTime	Game time passed since the last call.
	 */
	virtual void Tick(float DeltaTime) override;

	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId() const override;

	/*
	 * FootIK Feature
	 */
public:
	FSAAHandle CreateFootIK(ACharacter* InCharacter, const TArray<FName>& InBoneNames, float InTraceDistance = 50.f, float InTraceStart = 50.f, float InInterpSpeed = 18.f);
	FORCEINLINE FSimpleFootIK* FindFootIK(const FSAAHandle InHandle) { return FootIKs.Find(InHandle); }
	FFootIKInfo* FindFootIKInfo(const FSAAHandle InHandle, const FName& InBoneName);
	float FindFootIKOffset(const FSAAHandle InHandle, const FName& InBoneName);

protected:
	TMap<FSAAHandle, FSimpleFootIK> FootIKs;

protected:
	static FSimpleAdvancedAnimSystem* AdvancedAnimSystem;
};