// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Base.h"

void UGameplayAbility_Base::OnCompleted()
{
	Super::OnCompleted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Base::OnBlendOut()
{
	Super::OnBlendOut();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Base::OnInterrupted()
{
	Super::OnInterrupted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Base::OnCancelled()
{
	Super::OnCancelled();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
