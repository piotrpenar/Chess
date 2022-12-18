#pragma once
#include "EColor.h"
#include "Chess/Interfaces/ChessBoardProvider.h"
#include "ChessMovesData.generated.h"

USTRUCT()
struct FChessMovesData
{
	GENERATED_BODY()

	TArray<FVector2D> Directions;
	TScriptInterface<IChessBoardProvider> BoardProvider;
	EColor Color;
	FVector2D Position;

	FChessMovesData()
	{
	}
	FChessMovesData(TArray<FVector2D> Directions,TScriptInterface<IChessBoardProvider> Board,EColor Color,FVector2D Position)
	{
		this->Directions = Directions;
		this->BoardProvider = Board;
		this->Color = Color;
		this->Position = Position;
	}
};
