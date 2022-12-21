#include "ChessKnight.h"

#include "Chess/Helpers/ChessMovesHelper.h"

EFigure UChessKnight::GetFigureType()
{
	return EFigure::Knight;
}

TArray<FVector2D> UChessKnight::GetPossibleMoves()
{
	return {
		BoardPosition + FVector2D(-1, -2),
		BoardPosition + FVector2D(-2, -1),
		BoardPosition + FVector2D(1, -2),
		BoardPosition + FVector2D(2, -1),
		BoardPosition + FVector2D(1, 2),
		BoardPosition + FVector2D(2, 1),
		BoardPosition + FVector2D(-1, 2),
		BoardPosition + FVector2D(-2, 1),
	};
}

FChessMovesData UChessKnight::GenerateMovesData()
{
	return FChessMovesData(GetPossibleMoves(), BoardProvider, Color, BoardPosition,this);
}


TArray<FMove> UChessKnight::GetAvailableMoves()
{
	const FChessMovesData PossibleMovesData = GenerateMovesData();
	return UChessMovesHelper::GetValidMovesFromPositions(PossibleMovesData);
}
