// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"

#include "SimpleNetChannelType.h" // Plugin: SimpleNetChannel

#include "../Universal/UI_MsgLog.h"
#include "Elements/UI_CharacterSelectionList.h"
#include "Elements/UI_NameBox.h"

#include "UI_RoleHallMain.generated.h"


/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_RoleHallMain : public UUI_Base
{
	GENERATED_BODY()

	// Import MsgLog UI Widget
	UPROPERTY(meta = (BindWidget))
	UUI_MsgLog* UI_MsgLog;

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
	void PrintMsgLog(const FString& InMsgString) { PrintMsgLog(FText::FromString(InMsgString)); }
	void PrintMsgLog(const FText& InMsgText);

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
	void BindNetClientRcv();
	void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel);

	UFUNCTION()
	void LinkServerInfo(ESimpleNetErrorType InType, const FString& InMsg);

protected:
	void SpawnRecentCharacter();
	void HightLightDefaultSelectButton();

private:
	FDelegateHandle RecvDelegate;
};
