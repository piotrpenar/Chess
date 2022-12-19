﻿#include "ChessBishop.h"

#include "Chess/Helpers/ChessMovesHelper.h"

TArray<FMove> UChessBishop::GetAvailableMoves() 
{
	const TArray<FVector2D> Directions = {
		FVector2D(-1, -1),
		FVector2D(1, -1),
		FVector2D(1, 1),
		FVector2D(-1, 1),
	};
	return UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData(Directions,BoardProvider,Color,BoardPosition),ChessData);
}
