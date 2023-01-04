#include "ChessQueen.h"




EFigure UChessQueen::GetFigureType()
{
	return EFigure::Queen;
}


TArray<FIntPoint> UChessQueen::GetPossibleDirections() const
{
	return  {
		FIntPoint(-1, -1),
		FIntPoint(1, -1),
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
		FIntPoint(1, 0),
		FIntPoint(-1, 0),
		FIntPoint(0, -1),
		FIntPoint(0, 1),
	};
}

TArray<FMove> UChessQueen::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromDirections(GetPossibleDirections(),this);
}
