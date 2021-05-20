#include "DataTableEx.h"

#include "Serialization/BufferArchive.h"

UDataTableEx::UDataTableEx(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDataTableEx::PreSave(const class ITargetPlatform* targetPlatform)
{
	Super::PreSave(targetPlatform);

	Save();
}

void UDataTableEx::Save() const
{
	FBufferArchive buffer;
	for (auto c : GetTableAsCSV())
	{
		buffer << c;
	}

	FString savePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + GetName() + ".csv");
	FFileHelper::SaveArrayToFile(buffer, *savePath);
}
