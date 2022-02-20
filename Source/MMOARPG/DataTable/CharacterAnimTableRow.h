#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Animation/AnimMontage.h"

#include "CharacterAnimTableRow.generated.h"


USTRUCT(BlueprintType)
struct FCharacterAnimTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterAnimTableRow();

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAnim")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAnim")
	UAnimMontage* SwitchFightMontage;
	
};
