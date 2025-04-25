using UnrealBuildTool;

public class HowtoRedirectMat : ModuleRules
{
    public HowtoRedirectMat(ReadOnlyTargetRules Target) : base(Target)
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
                "MaterialEditor",
                "UnrealEd",
            }
        );
        
        PrivateIncludePaths.Add("Editor/MaterialEditor/Private");
    }
}