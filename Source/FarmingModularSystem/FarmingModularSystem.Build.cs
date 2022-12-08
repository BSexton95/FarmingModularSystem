// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FarmingModularSystem : ModuleRules
{
	public FarmingModularSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
