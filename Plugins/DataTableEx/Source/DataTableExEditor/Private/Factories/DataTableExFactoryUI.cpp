#include "DataTableExFactoryUI.h"

#include "DataTableEditorUtils.h"
#include "StructViewerFilter.h"
#include "StructViewerModule.h"

#define LOCTEXT_NAMESPACE "DataTableExFactory"

FReply FDataTableExFactoryUI::OnCreate()
{
	check(m_resultStruct);
	if (m_pickerWindow.IsValid())
	{
		m_pickerWindow->RequestDestroyWindow();
	}
	return FReply::Handled();
}

FReply FDataTableExFactoryUI::OnCancel()
{
	m_resultStruct = nullptr;
	if (m_pickerWindow.IsValid())
	{
		m_pickerWindow->RequestDestroyWindow();
	}
	return FReply::Handled();
}

bool FDataTableExFactoryUI::IsStructSelected() const
{
	return m_resultStruct != nullptr;
}

void FDataTableExFactoryUI::OnPickedStruct(const UScriptStruct* chosenStruct)
{
	m_resultStruct = chosenStruct;
	m_structPickerAnchor->SetIsOpen(false);
}

FText FDataTableExFactoryUI::OnGetComboTextValue() const
{
	return m_resultStruct ? FText::AsCultureInvariant(m_resultStruct->GetName()) : LOCTEXT("None", "None");
}

TSharedRef<SWidget> FDataTableExFactoryUI::GenerateStructPicker()
{
	class FDataTableExStructFilter : public IStructViewerFilter
	{
	public:
		virtual bool IsStructAllowed(
			const FStructViewerInitializationOptions& InInitOptions,
			const UScriptStruct* InStruct,
			TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			return FDataTableEditorUtils::IsValidTableStruct(InStruct);
		}

		virtual bool IsUnloadedStructAllowed(
			const FStructViewerInitializationOptions& InInitOptions,
			const FName InStructPath,
			TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override
		{
			return true;
		}
	};

	FStructViewerModule& structViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");

	// Fill in options
	FStructViewerInitializationOptions options;
	options.Mode = EStructViewerMode::StructPicker;
	options.StructFilter = MakeShared<FDataTableExStructFilter>();

	// clang-format off
	return
		SNew(SBox).
		WidthOverride(330)
		[
			SNew(SVerticalBox)

			+SVerticalBox::Slot()
				.FillHeight(1.0f)
				.MaxHeight(500)
				[
					SNew(SBorder)
						.Padding(4)
						.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
						[
							structViewerModule.CreateStructViewer(
								options,
								FOnStructPicked::CreateSP(this, &FDataTableExFactoryUI::OnPickedStruct))
						]
				]
		];
	// clang-format on
}

const UScriptStruct* FDataTableExFactoryUI::OpenStructSelector()
{
	FStructViewerModule& structViewerModule = FModuleManager::LoadModuleChecked<FStructViewerModule>("StructViewer");
	m_resultStruct = nullptr;

	// clang-format off
	m_pickerWindow =
		SNew(SWindow)
			.Title(LOCTEXT("DataTableFactoryOptions", "Pick Row Structure"))
			.ClientSize(FVector2D(350, 100))
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
				.Padding(10)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.AutoHeight()
					[
						SAssignNew(m_structPickerAnchor, SComboButton)
						.ContentPadding(FMargin(2, 2, 2, 1))
						.MenuPlacement(MenuPlacement_BelowAnchor)
						.ButtonContent()
						[
							SNew(STextBlock)
							.Text(this, &FDataTableExFactoryUI::OnGetComboTextValue)
						]
						.OnGetMenuContent(this, &FDataTableExFactoryUI::GenerateStructPicker)
					]
					+SVerticalBox::Slot()
					.HAlign(HAlign_Right)
					.AutoHeight()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SButton)
							.Text(LOCTEXT("OK", "OK"))
							.IsEnabled(this, &FDataTableExFactoryUI::IsStructSelected)
							.OnClicked(this, &FDataTableExFactoryUI::OnCreate)
						]
						+SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SButton)
							.Text(LOCTEXT("Cancel", "Cancel"))
							.OnClicked(this, &FDataTableExFactoryUI::OnCancel)
						]
					]
				]
			];
	// clang-format on

	GEditor->EditorAddModalWindow(m_pickerWindow.ToSharedRef());
	m_pickerWindow.Reset();

	return m_resultStruct;
}

#undef LOCTEXT_NAMESPACE // "DataTableExFactory"
