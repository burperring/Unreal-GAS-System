// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoulslikeGAS : ModuleRules
{
	public SoulslikeGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"GameplayAbilities", "GameplayTags", "GameplayTasks",
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" 
		});
	}
}
