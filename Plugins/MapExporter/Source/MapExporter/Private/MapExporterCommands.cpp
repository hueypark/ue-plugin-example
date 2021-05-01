// Copyright Epic Games, Inc. All Rights Reserved.

#include "MapExporterCommands.h"

#define LOCTEXT_NAMESPACE "FMapExporterModule"

void FMapExporterCommands::RegisterCommands()
{
	UI_COMMAND(
		PluginAction, "MapExporter", "Execute MapExporter action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
