#pragma once
#include "F2DBoardArray.generated.h"

USTRUCT(BlueprintType)
struct F2DBoardArray
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UObject*> Array;

	UObject* operator[](const int Index)
	{
		return Array[Index];
	}

	void operator=(const TArray<UObject*> NewArray)
	{
		Array = NewArray;
	}
	
	void Set(const int Index,UObject* Object)
	{
		Array[Index] = Object;
	}

	void Add(UObject* Object)
	{
		Array.Add(Object);
	}
};
