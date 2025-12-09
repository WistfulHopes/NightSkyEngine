// Copyright Screaming Goose Games. All Rights Reserved.

using UnrealBuildTool;

public class CollisionEditor : ModuleRules
{
	public CollisionEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[] {
                "CollisionEditor/Public",
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
				"GameplayTags",
				"GameplayTagsEditor"
            });
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			});
	}
}
