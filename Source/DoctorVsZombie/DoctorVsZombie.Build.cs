// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DoctorVsZombie : ModuleRules
{
	public DoctorVsZombie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Pixel2D", "Paper2D" });
    }
}
