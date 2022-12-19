#include "ChessKnight.h"

#include "Chess/Helpers/ChessMovesHelper.h"

TArray<FMove> UChessKnight::GetAvailableMoves() 
{
	TArray<FVector2D> PossibleMoves = {
		BoardPosition + FVector2D(-1, -2),
		BoardPosition + FVector2D(-2, -1),
		BoardPosition + FVector2D(1, -2),
		BoardPosition + FVector2D(2, -1),
		BoardPosition + FVector2D(1, 2),
		BoardPosition + FVector2D(2, 1),
		BoardPosition + FVector2D(-1, 2),
		BoardPosition + FVector2D(-2, 1),
	};
	return UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData(PossibleMoves,BoardProvider,Color,BoardPosition),ChessData);
}
