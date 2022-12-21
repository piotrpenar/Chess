#include "ChessBishop.h"

#include "Chess/Helpers/ChessMovesHelper.h"

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

FChessMovesData UChessBishop::GenerateMovesData()
{
	return FChessMovesData(GetPossibleDirections(), BoardProvider, Color, BoardPosition,this);
}

TArray<FMove> UChessBishop::GetAvailableMoves()
{
	const FChessMovesData PossibleMovesData = GenerateMovesData();
	return UChessMovesHelper::GetValidMovesFromDirections(PossibleMovesData);
}
