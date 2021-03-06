// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_MainBase.h"
#include "UI_PartnerList.generated.h"

class UVerticalBox;
class UUI_PartnerInfo;

/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_PartnerList : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* CharacterList;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUI_PartnerInfo> UI_PartnerInfoClass;
public:

	virtual void NativeConstruct();

	virtual void NativeDestruct();

public:
	// TMP
	void Init();

public:
	void TraverseListChildsByPredicate(TFunction<bool(UUI_PartnerInfo* InPartnerInfo)> InFunc);
};
