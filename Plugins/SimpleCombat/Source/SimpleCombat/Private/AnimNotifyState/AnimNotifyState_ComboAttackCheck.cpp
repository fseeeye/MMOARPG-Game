// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/AnimNotifyState_ComboAttackCheck.h"

#include "Interface/SimpleCombatInterface.h"
#include "SimpleComboType.h"

void UAnimNotifyState_ComboAttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ISimpleCombatInterface* Character = Cast<ISimpleCombatInterface>(MeshComp->GetOuter()))
	{
		Character->GetComboAttack()->bShortPress = false;
		Character->GetComboAttack()->OnUpdate();
	}
}

void UAnimNotifyState_ComboAttackCheck::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_ComboAttackCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	
	if (ISimpleCombatInterface* Character = Cast<ISimpleCombatInterface>(MeshComp->GetOuter()))
	{
		if (Character->GetComboAttack()->bLongPress || Character->GetComboAttack()->bShortPress)
		{
			Character->NormalAttack(ComboAbilityName);
		}
	}
}
