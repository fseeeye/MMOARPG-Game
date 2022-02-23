#include "Core/SimpleAdvancedAnimSystem.h"


FSimpleAdvancedAnimSystem* FSimpleAdvancedAnimSystem::AdvancedAnimSystem = nullptr;

FSimpleAdvancedAnimSystem* FSimpleAdvancedAnimSystem::Get()
{
	if (!AdvancedAnimSystem)
	{
		AdvancedAnimSystem = new FSimpleAdvancedAnimSystem();
	}

	return AdvancedAnimSystem;
}

void FSimpleAdvancedAnimSystem::Destory()
{
	if (AdvancedAnimSystem)
	{
		delete AdvancedAnimSystem;
		AdvancedAnimSystem = nullptr;
	}
}

void FSimpleAdvancedAnimSystem::Tick(float DeltaTime)
{
	for (auto &FootIK : FootIKs)
	{
		FootIK.Value.InnerTick(DeltaTime);
	}

	// Auto-Remove FootIK of pending kill character
	TArray<FSAAHandle> ShouldRemoveHandles;
	for (auto& FootIK : FootIKs)
	{
		if (FootIK.Value.IsCharacterPendingKill())
		{
			ShouldRemoveHandles.Add(FootIK.Key);
		}
	}

	for (auto& ShouldRemoveHandle : ShouldRemoveHandles)
	{
		FootIKs.Remove(ShouldRemoveHandle);
	}
}

TStatId FSimpleAdvancedAnimSystem::GetStatId() const
{
	return TStatId();
}

FSAAHandle FSimpleAdvancedAnimSystem::CreateFootIK(ACharacter* InCharacter, const TArray<FName>& InBoneNames, float InTraceDistance /*= 50.f*/, float InTraceStart /*= 50.f*/, float InInterpSpeed /*= 18.f*/)
{
	FSAAHandle Handle = FMath::RandRange(0, 999999);
	if (!FootIKs.Contains(Handle))
	{
		FSimpleFootIK& NewFootIK = FootIKs.Add(Handle, FSimpleFootIK());
		NewFootIK.Init(InCharacter, InBoneNames, InTraceDistance, InInterpSpeed);

		return Handle;
	}
	else
	{
		return CreateFootIK(InCharacter, InBoneNames, InTraceDistance, InInterpSpeed);
	}
}

FFootIKInfo* FSimpleAdvancedAnimSystem::FindFootIKInfo(const FSAAHandle InHandle, const FName& InBoneName)
{
	if (FSimpleFootIK* FootIK = FindFootIK(InHandle))
		return FootIK->GetInfo(InBoneName);

	return nullptr;
}

float FSimpleAdvancedAnimSystem::FindFootIKOffset(const FSAAHandle InHandle, const FName& InBoneName)
{
	if (FSimpleFootIK* FootIK = FindFootIK(InHandle))
		return FootIK->GetOffset(InBoneName);

	return 0.f;
}
