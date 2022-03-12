#pragma once

#include "CoreMinimal.h"
#include "MMOARPGGameType.generated.h"

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	NORMAL_STATE UMETA(DisplayName = "Normal"),
	FIGHT_STATE  UMETA(DisplayName = "Fight"),
	FLY_STATE    UMETA(DisplayName = "Fly"),
	CLIMB_STATE  UMETA(DisplayName = "Climb"),
	SWIM_STATE   UMETA(DisplayName = "Swim")
};

UENUM(BlueprintType)
enum class EFlyDodgeState : uint8
{
	NONE  UMETA(DisplayName = "None"),
	LEFT  UMETA(DisplayName = "Left"),
	RIGHT UMETA(DisplayName = "Right"),
};

struct FTimeBool
{
	FTimeBool()
		: bSet(false), Timer(0.f)
	{}

	explicit operator bool()
	{
		return bSet;
	}

	FTimeBool& operator=(bool bNewSet)
	{
		bSet = bNewSet;
		return *this;
	}

	FTimeBool& operator=(float InNewTime)
	{
		Timer = InNewTime;
		return *this;
	}

	bool operator*()
	{
		return bSet;
	}

	void NativeTick(float DeltaTime)
	{
		if (Timer > 0.f)
		{
			Timer -= DeltaTime;
			if (Timer <= 0.f)
			{
				FuncDelegate.ExecuteIfBound();
				Timer = 0.f;
				bSet = false;
			}
		}
	}

	bool bSet;
	float Timer;

	FSimpleDelegate FuncDelegate;
};
