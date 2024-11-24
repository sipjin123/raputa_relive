// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class ProjRelive : ModuleRules
{
	public ProjRelive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                "ProjRelive"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] 
        { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "UMG", "GameplayAbilities" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "WebSocket" });

        RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Config", "DefaultServerConfig.ini"));

    }
}
