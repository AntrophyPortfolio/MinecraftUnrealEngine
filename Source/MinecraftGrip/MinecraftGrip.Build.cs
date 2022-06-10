// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MinecraftGrip : ModuleRules
{
	public MinecraftGrip(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent", "AIModule", "NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });
		
		PrivateIncludePaths.AddRange(new string[]
		{
			"MinecraftGrip"
		});
		
		
	}
}