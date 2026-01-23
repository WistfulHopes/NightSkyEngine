using UnrealBuildTool;

public class RenderHotpatch : ModuleRules
{
	public RenderHotpatch(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			"UnrealEd"
		});
	}
}
