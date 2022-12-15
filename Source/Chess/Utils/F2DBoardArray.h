#pragma once
#include "Chess/ChessPieces/UChessPiece.h"
#include "F2DBoardArray.generated.h"

USTRUCT(BlueprintType)
struct F2DBoardArray
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UChessPiece*> Array;

	UChessPiece* operator[](int32 i)
	{
		return Array[i];
	}

	void operator=(TArray<UChessPiece*> newArray)
	{
		Array = newArray;
	}
	
	void Set(int i,UChessPiece* piece)
	{
		Array[i] = piece;
	}

	void Add(UChessPiece* piece)
	{
		Array.Add(piece);
	}
};
