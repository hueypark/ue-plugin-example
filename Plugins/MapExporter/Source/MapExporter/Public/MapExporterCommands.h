// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MapExporterStyle.h"

class FMapExporterCommands : public TCommands<FMapExporterCommands>
{
public:
	FMapExporterCommands()
		: TCommands<FMapExporterCommands>(
			  TEXT("MapExporter"),
			  NSLOCTEXT("Contexts", "MapExporter", "MapExporter Plugin"),
			  NAME_None,
			  FMapExporterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginAction;
};
