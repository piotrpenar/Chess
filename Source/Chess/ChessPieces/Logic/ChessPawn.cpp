#include "ChessPawn.h"

#include "Chess/Utils/F2DBoardArray.h"


TArray<FMove> UChessPawn::GetAvailableMoves() const
{
	const bool bIsWhite = Color == EColor::White;
	const int Direction = bIsWhite ? 1 : -1;
	FVector2D CurrentTargetPosition = BoardPosition;
	TArray<FMove> ValidMoves;
	TArray<FVector2D> PossibleMoves = {
		CurrentTargetPosition + FVector2D(-1, Direction),
		CurrentTargetPosition + FVector2D(0, Direction),
		CurrentTargetPosition + FVector2D(1, Direction),
	};

	if (!bHasMoved)
	{
		PossibleMoves.Add(BoardPosition + FVector2D(1, Direction * 2));
	}

	for (const FVector2D PossibleMove : PossibleMoves)
	{
		if (!(ChessData->IsValidPosition(PossibleMove)))
		{
			continue;
		}
		UChessPiece* TargetObject = GetOtherPieceAtPosition(PossibleMove);
		if (TargetObject && TargetObject->GetColor() == Color)
		{
			continue;
		}
		if (!TargetObject || TargetObject->GetColor() != Color && PossibleMove.X != BoardPosition.X)
		{
			ValidMoves.Add(FMove(PossibleMove, TargetObject));
		}
	}
	return ValidMoves;
}

void UChessPawn::MoveToPosition()
{
	Super::MoveToPosition();
	bHasMoved = true;
}
