#include "DataTableExFactory.h"

#include "DataTableEx.h"

UDataTableExFactory::UDataTableExFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UDataTableEx::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDataTableExFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDataTableEx>(InParent, InClass, InName, Flags);
}

bool UDataTableExFactory::ShouldShowInNewMenu() const
{
	return true;
}
