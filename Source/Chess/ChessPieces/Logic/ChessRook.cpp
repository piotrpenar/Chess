#include "ChessRook.h"

EFigure UChessRook::GetFigureType()
{
	return EFigure::Rook;
}

TArray<FIntPoint> UChessRook::GetPossibleDirections() const
{
	return {
		FIntPoint(1, 0),
		FIntPoint(-1, 0),
		FIntPoint(0, -1),
		FIntPoint(0, 1),
	};
}

TArray<FMove> UChessRook::GetAvailableMoves()
{
	return MovementRules->GetValidMovesFromDirections(GetPossibleDirections(), this);
}
