#include "ChessQueen.h"

#include "Chess/Helpers/ChessMovesHelper.h"


TArray<FMove> UChessQueen::GetAvailableMoves() 
{
	TArray<FVector2D> PossibleMoves = {
		FVector2D(-1, -1),
		FVector2D(1, -1),
		FVector2D(1, 1),
		FVector2D(-1, 1),
		FVector2D(1, 0),
		FVector2D(-1, 0),
		FVector2D(0, -1),
		FVector2D(0, 1),
	};
	return UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData(PossibleMoves,BoardProvider,Color,BoardPosition),ChessData);
}
