#include "DataTableExEditorModule.h"

#include "AssetTools/DataTableExActions.h"
#include "AssetToolsModule.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "DataTableExEditorModule"

void FDataTableExEditorModule::StartupModule()
{
	_RegisterAssetTools();

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDataTableExEditorModule::_RegisterToolMenu));
}

void FDataTableExEditorModule::ShutdownModule()
{
	_UnregisterAssetTools();

	UToolMenus::UnRegisterStartupCallback(this);
}

void FDataTableExEditorModule::SaveAllDataTableEx()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SaveAllDataFuncCalled","Save all data table ex!"));
}

void FDataTableExEditorModule::_RegisterAssetTools()
{
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	auto action = MakeShareable(new FDataTableExActions());

	assetTools.RegisterAssetTypeActions(action);
	m_registeredAssetTypeActions.Add(action);
}

void FDataTableExEditorModule::_RegisterToolMenu()
{
	UToolMenu* toolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	if (!toolbarMenu)
	{
		return;
	}

	toolbarMenu->FindOrAddSection("Settings")
		.AddEntry(FToolMenuEntry::InitToolBarButton(
			"Button", FUIAction(FExecuteAction::CreateStatic(&FDataTableExEditorModule::SaveAllDataTableEx)),
			LOCTEXT("SaveAllDataTableEx", "Save All Data"),
			LOCTEXT("SaveAllDataTableExTooltip", "Save all dataTableEx.")));
}

void FDataTableExEditorModule::_UnregisterAssetTools()
{
	FAssetToolsModule* assetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (!assetToolsModule)
	{
		return;
	}

	IAssetTools& assetTools = assetToolsModule->Get();

	for (auto action : m_registeredAssetTypeActions)
	{
		assetTools.UnregisterAssetTypeActions(action);
	}
}

IMPLEMENT_MODULE(FDataTableExEditorModule, DataTableExEditor)

#undef LOCTEXT_NAMESPACE
