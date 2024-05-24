// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NightSkyEngine : ModuleRules
{
	public NightSkyEngine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"InputCore",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"MovieScene",
			"LevelSequence",
			"EnhancedInput",
			"UMG",
			"Niagara",
			"Paper2D",
			"AdvancedSessions"
		});

		PrivateDependencyModuleNames.AddRange(new[] { "AIModule", "GGPOUE4", "Json", "CommonUI", "CommonInput", "GameplayTags", "CinematicCamera" });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
