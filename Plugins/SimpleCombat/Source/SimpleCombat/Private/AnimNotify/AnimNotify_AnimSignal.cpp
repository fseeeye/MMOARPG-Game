// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_AnimSignal.h"

#include "Interface/SimpleCombatInterface.h"


UAnimNotify_AnimSignal::UAnimNotify_AnimSignal()
	: SignalValue(INDEX_NONE)
{

}

FString UAnimNotify_AnimSignal::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_AnimSignal::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (ISimpleCombatInterface* SimpleCombatInterface = Cast<ISimpleCombatInterface>(MeshComp->GetOuter()))
	{
		SimpleCombatInterface->AnimSignal(SignalValue);
	}
}
