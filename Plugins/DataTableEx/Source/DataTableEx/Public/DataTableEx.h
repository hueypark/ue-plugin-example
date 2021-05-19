#pragma once

#include "Engine/DataTable.h"

#include "DataTableEx.generated.h"

// 언리얼 엔진 기본 데이터 테이블의 확장버전 입니다.
UCLASS(BlueprintType)
class DATATABLEEX_API UDataTableEx : public UDataTable
{
	GENERATED_UCLASS_BODY()

public:
	// 저장합니다.
	void Save() const;
};
