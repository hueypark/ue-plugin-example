﻿// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DataTableExEditor : ModuleRules
{
	public DataTableExEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				"TextAssetEditor",
			}
			);


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
				"DataTableEx",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
