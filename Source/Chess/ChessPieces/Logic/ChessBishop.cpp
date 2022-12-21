#include "ChessBishop.h"

#include "Chess/Helpers/ChessMovesHelper.h"

EFigureType UChessBishop::GetFigureType()
{
	return EFigureType::Bishop;
}

TArray<FMove> UChessBishop::GetAvailableMoves()
{
	const TArray<FVector2D> Directions = {
		FVector2D(-1, -1),
		FVector2D(1, -1),
		FVector2D(1, 1),
		FVector2D(-1, 1),
	};
	return UChessMovesHelper::GetValidMovesFromDirections(
		FChessMovesData(Directions, BoardProvider, Color, BoardPosition,this), BoardProvider.GetInterface());
}
