#include "ChessKing.h"


EFigure UChessKing::GetFigureType()
{
	return EFigure::King;
}

TArray<FIntPoint> UChessKing::GetPossiblePositions() const
{
	return {
		BoardPosition + FIntPoint(-1, -1),
		BoardPosition + FIntPoint(-1, 0),
		BoardPosition + FIntPoint(-1, 1),
		BoardPosition + FIntPoint(0, 1),
		BoardPosition + FIntPoint(1, 1),
		BoardPosition + FIntPoint(1, 0),
		BoardPosition + FIntPoint(1, -1),
		BoardPosition + FIntPoint(0, -1),
	};
}

TArray<FMove> UChessKing::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(),this);
}
