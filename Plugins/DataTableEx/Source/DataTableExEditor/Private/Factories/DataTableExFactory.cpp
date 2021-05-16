#include "DataTableExFactory.h"

#include "DataTableEx.h"
#include "DataTableExFactoryUI.h"
#include "StructViewerModule.h"

#define LOCTEXT_NAMESPACE "DataTableFactory"

UDataTableExFactory::UDataTableExFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UDataTableEx::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

bool UDataTableExFactory::ConfigureProperties()
{
	TSharedRef<FDataTableExFactoryUI> structSelector = MakeShareable(new FDataTableExFactoryUI());
	m_struct = structSelector->OpenStructSelector();

	return m_struct != nullptr;
}

UObject* UDataTableExFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDataTableEx* dataTableEx = nullptr;
	if (m_struct && ensure(SupportedClass == InClass))
	{
		dataTableEx = NewObject<UDataTableEx>(InParent, InName, Flags);
		if (dataTableEx)
		{
			dataTableEx->RowStruct = const_cast<UScriptStruct*>(m_struct);
		}
	}

	return dataTableEx;
}

bool UDataTableExFactory::ShouldShowInNewMenu() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE // "DataTableFactory"
