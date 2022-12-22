#include "ChessKing.h"


EFigure UChessKing::GetFigureType()
{
	return EFigure::King;
}

TArray<FVector2D> UChessKing::GetPossiblePositions() const
{
	return {
		BoardPosition + FVector2D(-1, -1),
		BoardPosition + FVector2D(-1, 0),
		BoardPosition + FVector2D(-1, 1),
		BoardPosition + FVector2D(0, 1),
		BoardPosition + FVector2D(1, 1),
		BoardPosition + FVector2D(1, 0),
		BoardPosition + FVector2D(1, -1),
		BoardPosition + FVector2D(0, -1),
	};
}

TArray<FMove> UChessKing::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(),this);
}
