// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjRelive : ModuleRules
{
	public ProjRelive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "UMG", "GameplayAbilities" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "WebSocket" });
	}
}
