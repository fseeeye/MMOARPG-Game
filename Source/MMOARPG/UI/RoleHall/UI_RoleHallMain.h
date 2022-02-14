// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_MainBase.h"

// Components
#include "Elements/UI_CharacterSelectionList.h"
#include "Elements/UI_NameBox.h"

#include "UI_RoleHallMain.generated.h"


/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_RoleHallMain : public UUI_MainBase
{
	GENERATED_BODY()

	// Import Character Selection List UI Widget
	UPROPERTY(meta = (BindWidget))
	UUI_CharacterSelectionList* UI_CharacterSelectionList;

	// Import Character Name Box UI Widget
	UPROPERTY(meta = (BindWidget))
	UUI_NameBox* UI_NameBox;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	FORCEINLINE void PlayNameBoxShowUpAnim() { UI_NameBox->PlayWidgetAnim(TEXT("ShowUp")); }
	FORCEINLINE void PlayNameBoxShowOffAnim() { UI_NameBox->PlayWidgetAnim(TEXT("ShowOff")); }
	FORCEINLINE void SetNameBoxSlotPosition(const int32 InSlotPos) { UI_NameBox->SetSlotPosition(InSlotPos); }

	void ResetCharacterSelectionList(bool bSpawnCharacter = true);

	void CheckCharacterNameInServer(FString& InCharacterName);
	void CreateCharacterInServer(const FMMOARPGCharacterAppearance& InCA);
	void PrintMsgLogCheckName(ECheckNameType InCheckNameType);

	void JoinDSServer(int32 InSlotPos);

protected:
	void RoleHallMainShowUp();
	void RoleHallMainShowOff();

protected:
	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) override;
	virtual void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg) override;

protected:
	void SpawnRecentCharacter();
	void HightLightDefaultSelectButton();

private:
	FDelegateHandle RecvDelegate;
};
