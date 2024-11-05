// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class ProjReliveServerTarget : TargetRules
{
    public ProjReliveServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.Latest;        
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bUseLoggingInShipping = true;
        ExtraModuleNames.AddRange( new string[] { "ProjRelive" } );
    }
}
