#include "ChessBishop.h"

EFigure UChessBishop::GetFigureType()
{
	return EFigure::Bishop;
}

TArray<FIntPoint> UChessBishop::GetPossibleDirections() const
{
	return {
		FIntPoint(-1, -1),
		FIntPoint(1, -1),
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
	};
}

TArray<FMove> UChessBishop::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromDirections(GetPossibleDirections(), this);
}
