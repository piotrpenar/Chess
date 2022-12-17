#pragma once
#include "EColor.h"
#include "F2DBoardArray.h"
#include "ChessMovesData.generated.h"

USTRUCT()
struct FChessMovesData
{
	GENERATED_BODY()

	TArray<FVector2D> Directions;
	TArray<F2DBoardArray> Board;
	EColor Color;
	FVector2D Position;

	FChessMovesData()
	{
	}
	FChessMovesData(TArray<FVector2D> Directions,TArray<F2DBoardArray> Board,EColor Color,FVector2D Position)
	{
		this->Directions = Directions;
		this->Board = Board;
		this->Color = Color;
		this->Position = Position;
	}
};
