#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

class FDataTableExEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	// 모든 DataTableEx 를 저장합니다.
	static void SaveAllDataTableEx();

private:
	// 에셋 툴을 등록합니다.
	void _RegisterAssetTools();

	// 툴바 메뉴를 등록합니다.
	void _RegisterToolMenu();

	// 에셋 툴을 해제합니다.
	void _UnregisterAssetTools();

private:
	// 등록된 에셋 타입 액션들
	TArray<TSharedRef<IAssetTypeActions>> m_registeredAssetTypeActions;
};
