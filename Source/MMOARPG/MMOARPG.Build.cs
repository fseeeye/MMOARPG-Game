// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MMOARPG : ModuleRules
{
	public MMOARPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			// Engine Plugin Modules
			"SimpleNetChannel",
			"SimpleThread",
			"MMOARPGComm",
			// Project Plugin Modules
			"SimpleActorBrowsing",
			"SimpleCombat",
			"SimpleAdvancedAnimation"
		});
	}
}
