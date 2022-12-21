#include "ChessQueen.h"

#include "Chess/Helpers/ChessMovesHelper.h"


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

FChessMovesData UChessQueen::GenerateMovesData()
{
	return FChessMovesData(GetPossibleDirections(), BoardProvider, Color, BoardPosition,this);
}

TArray<FMove> UChessQueen::GetAvailableMoves()
{
	const FChessMovesData PossibleMovesData = GenerateMovesData();
	return UChessMovesHelper::GetValidMovesFromDirections(PossibleMovesData);
}
