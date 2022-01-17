// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"


class FSimpleChannel;
/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
	inline void SetWidgetParent(UWidget* InWidget) { ParentWidget = InWidget; }
	template<class T>
	inline T* GetWidgetParent() { return Cast<T>(ParentWidget); }

protected:
	template<class T>
	T* GetGameInstance()
	{
		return GetWorld() != nullptr ? GetWorld()->GetGameInstance<T>() : nullptr;
	}

	template<class T>
	T* GetGameController()
	{
		return GetWorld() != nullptr ? GetWorld()->GetFirstPlayerController<T>() : nullptr;
	}

	template<class T>
	T* GetPawn()
	{
		return GetWorld() != nullptr ? 
			(GetWorld()->GetFirstPlayerController() != nullptr ? GetWorld()->GetFirstPlayerController()->GetPawn<T>() : nullptr)
			: nullptr;
	}

protected:
	virtual void RecvProtocol(uint32 ProtocolNumber, FSimpleChannel* Channel) {}

	UWidgetAnimation* GetWidgetAnmi(const FString &InWidgetAnmiName);
	void PlayWidgetAnim(const FString& InWidgetAnmiName);

protected:
	UPROPERTY()
	UWidget* ParentWidget;
};
