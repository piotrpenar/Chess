#include "ChessKing.h"


TArray<FMove> UChessKing::GetAvailableMoves() const
{
	FVector2D CurrentTargetPosition = BoardPosition;
	TArray<FMove> ValidMoves;
	TArray<FVector2D> PossibleMoves = {
		CurrentTargetPosition + FVector2D(-1, -2),
		CurrentTargetPosition + FVector2D(-2, -1),
		CurrentTargetPosition + FVector2D(1, -2),
		CurrentTargetPosition + FVector2D(2, -1),
		CurrentTargetPosition + FVector2D(1, 2),
		CurrentTargetPosition + FVector2D(2, 1),
		CurrentTargetPosition + FVector2D(-1, 2),
		CurrentTargetPosition + FVector2D(-2, 1),
	};

	for (const FVector2D PossibleMove  : PossibleMoves)
	{
		if (!(ChessData->IsValidPosition(PossibleMove)))
		{
			continue;
		}
		UChessPiece* TargetObject = GetOtherPieceAtPosition(PossibleMove);
		if (!TargetObject || TargetObject->GetColor() != Color)
		{
			ValidMoves.Add(FMove(PossibleMove, TargetObject));
		}
	}
	return ValidMoves;
}