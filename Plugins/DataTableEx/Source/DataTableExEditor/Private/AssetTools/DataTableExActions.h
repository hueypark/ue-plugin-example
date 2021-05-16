#pragma once

#include "AssetTypeActions_Base.h"

class FDataTableExActions : public FAssetTypeActions_Base
{
public:
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
};
