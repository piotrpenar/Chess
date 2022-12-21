#pragma once
#include "EColor.h"
#include "Chess/ChessPieces/ChessPiece.h"
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
	UChessPiece* ChessPiece;

	FChessMovesData()
	{
	}
	FChessMovesData(TArray<FVector2D> Directions,TScriptInterface<IChessBoardProvider> Board,EColor Color,FVector2D Position,UChessPiece* ChessPiece)
	{
		this->Directions = Directions;
		this->BoardProvider = Board;
		this->Color = Color;
		this->Position = Position;
		this->ChessPiece = ChessPiece;
	}
};
