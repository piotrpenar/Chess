#include "ChessBishop.h"

#include "Chess/Helpers/ChessMovesHelper.h"

TArray<FMove> UChessBishop::GetAvailableMoves() const
{
	TArray<FVector2D> PossibleMoves = {
		BoardPosition + FVector2D(-1, -1),
		BoardPosition + FVector2D(1, -1),
		BoardPosition + FVector2D(1, 1),
		BoardPosition + FVector2D(-1, 1),
	};
	return UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData(PossibleMoves,Board,Color,BoardPosition),ChessData);
}
