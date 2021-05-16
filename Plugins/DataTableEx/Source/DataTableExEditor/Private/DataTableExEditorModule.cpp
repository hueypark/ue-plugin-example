#include "DataTableExEditorModule.h"

#include "AssetTools/DataTableExActions.h"
#include "AssetToolsModule.h"

void FDataTableExEditorModule::StartupModule()
{
	_RegisterAssetTools();
}

void FDataTableExEditorModule::ShutdownModule()
{
	_UnregisterAssetTools();
}

void FDataTableExEditorModule::_RegisterAssetTools()
{
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	auto action = MakeShareable(new FDataTableExActions());

	assetTools.RegisterAssetTypeActions(action);
	m_registeredAssetTypeActions.Add(action);
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
