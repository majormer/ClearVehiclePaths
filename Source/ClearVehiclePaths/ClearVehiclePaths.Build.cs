using UnrealBuildTool;

public class ClearVehiclePaths : ModuleRules
{
	public ClearVehiclePaths(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp20;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"SML",
			"FactoryGame"
		});
	}
}
