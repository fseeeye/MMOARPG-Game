// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MsgLog.h"

void UUI_MsgLog::PlayTextAnim()
{
	PlayWidgetAnim(TEXT("ShowText"));
}

void UUI_MsgLog::SetText(const FText& InText)
{
	MsgLog->SetText(InText);
}
