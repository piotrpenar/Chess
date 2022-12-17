#include "ChessKing.h"
#include "Chess/Helpers/ChessMovesHelper.h"


TArray<FMove> UChessKing::GetAvailableMoves() const
{
	TArray<FVector2D> PossibleMoves = {
		BoardPosition + FVector2D(-1, -1),
		BoardPosition + FVector2D(-1, 0),
		BoardPosition + FVector2D(-1, 1),
		BoardPosition + FVector2D(0, 1),
		BoardPosition + FVector2D(1, 1),
		BoardPosition + FVector2D(1, 0),
		BoardPosition + FVector2D(1, -1),
		BoardPosition + FVector2D(0, -1),
	};
	return UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData(PossibleMoves,Board,Color,BoardPosition),ChessData);
}
