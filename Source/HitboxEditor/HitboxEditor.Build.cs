// Copyright Screaming Goose Games. All Rights Reserved.

using UnrealBuildTool;

public class HitboxEditor : ModuleRules
{
	public HitboxEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                "HitboxEditor/Public",
				// Because the other way wasn't working for me, fix later
				"NightSkyEngine"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine"
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "NightSkyEngine",
				"UnrealEd",
				"AssetTools",
				"EditorFramework",
				"EditorStyle",
                "Slate",
                "SlateCore",
				"InputCore",
				"EditorWidgets",
				"PropertyEditor",
				"AdvancedPreviewScene",
            });
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			});
	}
}
