#include "DataTableExActions.h"

#include "DataTableEditorModule.h"
#include "DataTableEx.h"
#include "IDataTableEditor.h"

#define LOCTEXT_NAMESPACE "DataTableExFactory"

uint32 FDataTableExActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FDataTableExActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_DataTableEx", "Data Table Ex");
}

UClass* FDataTableExActions::GetSupportedClass() const
{
	return UDataTableEx::StaticClass();
}

FColor FDataTableExActions::GetTypeColor() const
{
	return FColor::White;
}

void FDataTableExActions::OpenAssetEditor(
	const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	FDataTableEditorModule& dataTableEditorModule =
		FModuleManager::LoadModuleChecked<FDataTableEditorModule>("DataTableEditor");

	for (auto iter = InObjects.CreateConstIterator(); iter; ++iter)
	{
		auto dataTableEx = Cast<UDataTableEx>(*iter);

		TSharedRef<IDataTableEditor> dataTableEditor =
			dataTableEditorModule.CreateDataTableEditor(EToolkitMode::Standalone, EditWithinLevelEditor, dataTableEx);

		TSharedPtr<FExtender> toolbarExtender = MakeShareable(new FExtender);
		toolbarExtender->AddToolBarExtension(
			"Asset", EExtensionHook::After, nullptr,
			FToolBarExtensionDelegate::CreateLambda(
				[](FToolBarBuilder& toolbarBuilder)
				{
					toolbarBuilder.BeginSection("DataTableEx");
					{
						toolbarBuilder.AddToolBarButton(
							FUIAction(FExecuteAction::CreateLambda(
								[]()
								{
								})),
							NAME_None, LOCTEXT("ExportIconText", "Export"),
							LOCTEXT("ExportToolTip", "Export data table"),
							FSlateIcon(FEditorStyle::GetStyleSetName(), "DataTableEditor.Export"));
					}
				}));
		dataTableEditor->AddToolbarExtender(toolbarExtender);

		dataTableEditor->RegenerateMenusAndToolbars();
	}
}

#undef LOCTEXT_NAMESPACE // "DataTableExFactory"
