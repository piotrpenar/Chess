#include "ChessKing.h"

EFigure UChessKing::GetFigureType()
{
	return EFigure::King;
}

TArray<FIntPoint> UChessKing::GetPossiblePositions() const
{
	return {
		BoardPosition + FIntPoint(-1, -1),
		BoardPosition + FIntPoint(-1, 0),
		BoardPosition + FIntPoint(-1, 1),
		BoardPosition + FIntPoint(0, 1),
		BoardPosition + FIntPoint(1, 1),
		BoardPosition + FIntPoint(1, 0),
		BoardPosition + FIntPoint(1, -1),
		BoardPosition + FIntPoint(0, -1),
	};
}

TArray<FMove> UChessKing::GetAvailableMoves()
{
	TArray<FMove> ValidMoves = MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(), this);
	TArray<FMove> SpecialMoves = MovementVerifier->GetValidSpecialMoves(this);
	ValidMoves.Append(SpecialMoves);
	return ValidMoves;
}
