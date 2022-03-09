// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGAnimInstanceBase.h"

#include "../../Character/MMOARPGCharacterBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SimpleAdvancedAnimationBPLibrary.h"

UMMOARPGAnimInstanceBase::UMMOARPGAnimInstanceBase()
	: bDeath(false)
	, bInAir(false)
	, Speed(0.f)
	, ActionState(ECharacterActionState::NORMAL_STATE)
	, bFootIK(false)
	, FootIK_ID(INDEX_NONE)
	, FootIK_LeftBoneName(TEXT("foot_l"))
	, FootIK_RightBoneName(TEXT("foot_r"))
{
}

void UMMOARPGAnimInstanceBase::InitAnimInstance(ACharacter* InCharacter)
{
	// Init FootIK
	if (bFootIK)
	{
		// TMP
		FootIK_BoneNames.Add(FootIK_LeftBoneName);
		FootIK_BoneNames.Add(FootIK_RightBoneName);

		FootIK_ID = USimpleAdvancedAnimationBPLibrary::CreateFootIK(InCharacter, FootIK_BoneNames);
	}
}

void UMMOARPGAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMMOARPGAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AMMOARPGCharacterBase* CharacterBase = Cast<AMMOARPGCharacterBase>(TryGetPawnOwner()))
	{
		// Get forward velocity
		Speed = CharacterBase->GetVelocity().Size();
		// Get is falling (in air)
		bInAir = CharacterBase->GetMovementComponent()->IsFalling();
		// Get is fight from CharacterBase class
		ActionState = CharacterBase->GetActionState();
	}

	// FootIK update offsets
	if (bFootIK && FootIK_ID != INDEX_NONE)
	{
		// TMP
		TArray<float> OffsetArray;
		float LOffset = GetFootIKOffset(FootIK_LeftBoneName);
		float ROffset = GetFootIKOffset(FootIK_RightBoneName);

		OffsetArray.Add(LOffset);
		OffsetArray.Add(ROffset);
		FootIK_CentroidOffsetZ = USimpleAdvancedAnimationBPLibrary::CalculateFootIKCentroidOffsetZ(OffsetArray);

		// Tips: might be reverse in different mesh
		FootIK_LeftOffset  = -(FootIK_CentroidOffsetZ - LOffset);
		FootIK_RightOffset = FootIK_CentroidOffsetZ - ROffset;
	}
}

float UMMOARPGAnimInstanceBase::GetFootIKOffset(const FName& InBoneName)
{
	if (FootIK_ID != INDEX_NONE)
	{
		return USimpleAdvancedAnimationBPLibrary::FindFootIKOffset(FootIK_ID, InBoneName);
	}

	return 0.f;
}
