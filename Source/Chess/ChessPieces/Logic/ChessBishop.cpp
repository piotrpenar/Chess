#include "ChessBishop.h"

EFigure UChessBishop::GetFigureType()
{
	return EFigure::Bishop;
}

TArray<FVector2D> UChessBishop::GetPossibleDirections() const
{
	return  {
		FVector2D(-1, -1),
		FVector2D(1, -1),
		FVector2D(1, 1),
		FVector2D(-1, 1),
	};
}

TArray<FMove> UChessBishop::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromDirections(GetPossibleDirections(),this);
}
