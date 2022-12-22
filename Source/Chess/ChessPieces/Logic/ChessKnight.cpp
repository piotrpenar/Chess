#include "ChessKnight.h"


EFigure UChessKnight::GetFigureType()
{
	return EFigure::Knight;
}

TArray<FVector2D> UChessKnight::GetPossiblePositions()
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


TArray<FMove> UChessKnight::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(),this);
}
