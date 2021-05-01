// Copyright Epic Games, Inc. All Rights Reserved.

#include "MapExporter.h"

#include "MapExporterCommands.h"
#include "MapExporterStyle.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName MapExporterTabName("MapExporter");

#define LOCTEXT_NAMESPACE "FMapExporterModule"

void FMapExporterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
	// file per-module

	FMapExporterStyle::Initialize();
	FMapExporterStyle::ReloadTextures();

	FMapExporterCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMapExporterCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMapExporterModule::PluginButtonClicked), FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMapExporterModule::RegisterMenus));
}

void FMapExporterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMapExporterStyle::Shutdown();

	FMapExporterCommands::Unregister();
}

void FMapExporterModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
		FText::FromString(TEXT("FMapExporterModule::PluginButtonClicked()")),
		FText::FromString(TEXT("MapExporter.cpp")));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMapExporterModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMapExporterCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry =
					Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMapExporterCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMapExporterModule, MapExporter)
