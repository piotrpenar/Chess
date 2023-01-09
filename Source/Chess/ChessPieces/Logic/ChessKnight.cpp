#include "ChessKnight.h"

EFigure UChessKnight::GetFigureType()
{
	return EFigure::Knight;
}

TArray<FIntPoint> UChessKnight::GetPossiblePositions()
{
	return {
		BoardPosition + FIntPoint(-1, -2),
		BoardPosition + FIntPoint(-2, -1),
		BoardPosition + FIntPoint(1, -2),
		BoardPosition + FIntPoint(2, -1),
		BoardPosition + FIntPoint(1, 2),
		BoardPosition + FIntPoint(2, 1),
		BoardPosition + FIntPoint(-1, 2),
		BoardPosition + FIntPoint(-2, 1),
	};
}


TArray<FMove> UChessKnight::GetAvailableMoves()
{
	return MovementRules->GetValidMovesFromPositions(GetPossiblePositions(), this);
}
