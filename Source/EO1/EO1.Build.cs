// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EO1 : ModuleRules
{
	public EO1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"EO1",
			"EO1/Variant_Platforming",
			"EO1/Variant_Platforming/Animation",
			"EO1/Variant_Combat",
			"EO1/Variant_Combat/AI",
			"EO1/Variant_Combat/Animation",
			"EO1/Variant_Combat/Gameplay",
			"EO1/Variant_Combat/Interfaces",
			"EO1/Variant_Combat/UI",
			"EO1/Variant_SideScrolling",
			"EO1/Variant_SideScrolling/AI",
			"EO1/Variant_SideScrolling/Gameplay",
			"EO1/Variant_SideScrolling/Interfaces",
			"EO1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
