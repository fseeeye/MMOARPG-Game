// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"

UWidgetAnimation* UUI_Base::GetWidgetAnmi(const FString& InWidgetAnmiName)
{
	// Get BluePrint Class
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGeneratedClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		// Get all Animations in BluePrint
		TArray<UWidgetAnimation*> InternalAnimations = WidgetBlueprintGeneratedClass->Animations;
		// Find target Animation
		UWidgetAnimation** TargetAnimation = InternalAnimations.FindByPredicate(
			[&](const UWidgetAnimation* Animation)
			{
				return Animation->GetFName().ToString() == (InWidgetAnmiName + FString("_INST"));
			}
		);

		return *TargetAnimation;
	}

	return nullptr;
}

void UUI_Base::PlayWidgetAnim(const FString& InWidgetAnmiName)
{
	if (UWidgetAnimation* TargetAnimation = GetWidgetAnmi(InWidgetAnmiName))
	{
		PlayAnimation(TargetAnimation);
	}
}
