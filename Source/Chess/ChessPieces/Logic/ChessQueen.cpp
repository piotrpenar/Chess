#include "ChessQueen.h"




EFigure UChessQueen::GetFigureType()
{
	return EFigure::Queen;
}


TArray<FVector2D> UChessQueen::GetPossibleDirections() const
{
	return  {
		FVector2D(-1, -1),
		FVector2D(1, -1),
		FVector2D(1, 1),
		FVector2D(-1, 1),
		FVector2D(1, 0),
		FVector2D(-1, 0),
		FVector2D(0, -1),
		FVector2D(0, 1),
	};
}

TArray<FMove> UChessQueen::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromDirections(GetPossibleDirections(),this);
}
