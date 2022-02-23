#pragma once

#include "CoreMinimal.h"
#include "SimpleAdvancedAnimationType.generated.h"


typedef int32 FSAAHandle;

USTRUCT(BlueprintType)
struct FFootIKInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AdvancedAnimation|FootIKInfo")
	float Offset;
};