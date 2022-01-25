// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"

// Components & UObject
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "UI_CharacterButton.h"
#include "UI_KneadFace.h"
#include "../../../Core/RoleHall/Character/RoleHallCharacterStage.h"

// Plugins
#include "MMOARPGCommType.h"

#include "UI_CharacterSelectionList.generated.h"

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_CharacterSelectionList : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ListName;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* List;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUI_CharacterButton> UI_CharacterButtonSubClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUI_KneadFace> UI_KneadFaceSubClass;

	UPROPERTY(EditDefaultsOnly, Category = "AssociationCharacter")
	TSubclassOf<ARoleHallCharacterStage> RoleHallCharacterStageClass;

	UPROPERTY(EditDefaultsOnly, Category = "AssociationCharacter")
	FVector RoleHallCharacterSpawnPoint;
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void CreateKneadFacePanel();
	void CreateCharacterButtons();

	void SpawnCharacterStage(const int32 InSlotPos);
	void SpawnCharacterStage(const FMMOARPGCharacterAppearance* InCA);
	void SpawnCharacterStage();
	ARoleHallCharacterStage* CreateCharacterStage();

	void HightLightButton(int32 InSlotPos);
	FORCEINLINE void SetCurrentSlotPos(const int32 InSlotPos) {
		CurrentSelectedSlotPos = InSlotPos;
		//HightLightButton(CurrentSelectedSlotPos);
	}

	template<class T>
	void FindByPredicateInList(TFunction<bool(T*)> InFunc)
	{
		for (auto& Child : List->GetAllChildren())
		{
			if (T* Tmp = Cast<T>(Child))
			{
				if (InFunc(Tmp))
				{
					break;
				}
			}
		}
	};

protected:
	void InitCharacterButtons(FMMOARPGCharacterAppearances& InCAs);

protected:
	int32 CurrentSelectedSlotPos;
};
