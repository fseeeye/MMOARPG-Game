#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Animation/AnimMontage.h"
#include "../Core/Game/Character/MMOARPGCharacterBase.h"

#include "CharacterStyleTableRow.generated.h"


USTRUCT(BlueprintType)
struct FCharacterStyleTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterStyleTableRow();

	UPROPERTY(EditDefaultsOnly, Category = "CharacterStyle")
	int32 CharacterID;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterStyle")
	TSubclassOf<AMMOARPGCharacterBase> CharacterClass;
};
