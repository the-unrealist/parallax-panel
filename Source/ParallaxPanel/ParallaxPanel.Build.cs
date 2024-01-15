// Copyright (c) 2024 citrus - https://unrealist.org
// Licensed under the MIT License.

using UnrealBuildTool;

public class ParallaxPanel : ModuleRules
{
    public ParallaxPanel(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "Core",
                "CoreUObject",
                "SlateCore",
                "UMG"
            });
    }
}
