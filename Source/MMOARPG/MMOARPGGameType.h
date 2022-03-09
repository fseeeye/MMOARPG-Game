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
