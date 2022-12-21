#pragma once
#include "F2DBoardArray.generated.h"

USTRUCT(BlueprintType)
struct F2DBoardArray
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UObject*> Array;

	F2DBoardArray(){}
	
	F2DBoardArray(F2DBoardArray other)
	{
		for(UObject* TargetObject : other.Array)
		{
			Array.Add(NewObject<IClo>())
		}
	}

	UObject* operator[](int32 i)
	{
		return Array[i];
	}

	void operator=(TArray<UObject*> newArray)
	{
		Array = newArray;
	}
	
	void Set(int i,UObject* piece)
	{
		Array[i] = piece;
	}

	void Add(UObject* piece)
	{
		Array.Add(piece);
	}
};
