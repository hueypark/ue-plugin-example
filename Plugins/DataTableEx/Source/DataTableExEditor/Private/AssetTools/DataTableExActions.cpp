#include "DataTableExActions.h"

#include "DataTableEx.h"

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
