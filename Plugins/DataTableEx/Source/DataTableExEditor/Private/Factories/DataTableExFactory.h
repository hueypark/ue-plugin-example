#pragma once

#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"

#include "DataTableExFactory.generated.h"

UCLASS()
class UDataTableExFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

public:
	virtual UObject* FactoryCreateNew(
		UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
		override;

	virtual bool ShouldShowInNewMenu() const override;
};
