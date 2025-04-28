using UnrealBuildTool;

public class HowtoFixContent : ModuleRules
{
    public HowtoFixContent(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "EditorWidgets",
                "ContentBrowserData",
                "UnrealEd",
            }
        );
    }
}