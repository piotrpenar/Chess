#pragma once
#include "CPUDifficulty.generated.h"


USTRUCT(BlueprintType)
struct FCPUDifficulty
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int EloValue = 0;
};
