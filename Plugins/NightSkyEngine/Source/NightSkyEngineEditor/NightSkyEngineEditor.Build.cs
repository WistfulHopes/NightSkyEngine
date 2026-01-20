using UnrealBuildTool;

public class NightSkyEngineEditor : ModuleRules
{
    public NightSkyEngineEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PrivateIncludePaths.AddRange(
            new string[] {
                "NightSkyEngineEditor/Public",
                "NightSkyEngine"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "NightSkyEngine",
                "GameplayTags",
            }
        );
    }
}