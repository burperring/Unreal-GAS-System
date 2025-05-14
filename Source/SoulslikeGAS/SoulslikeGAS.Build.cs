// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoulslikeGAS : ModuleRules
{
	public SoulslikeGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
