#include "ChessPawn.h"


EFigure UChessPawn::GetFigureType()
{
	return EFigure::Pawn;
}

TArray<FVector2D> UChessPawn::GetPossiblePositions()
{
	const bool bIsWhite = Color == EColor::White;
	const int Direction = bIsWhite ? 1 : -1;
	TArray PossibleMoves = {
		BoardPosition + FVector2D(-1, Direction),
		BoardPosition + FVector2D(0, Direction),
		BoardPosition + FVector2D(1, Direction),
	};
	if (!bHasMoved)
	{
		PossibleMoves.Add(BoardPosition + FVector2D(0, Direction * 2));
	}
	return PossibleMoves;
}

void UChessPawn::MoveToPosition(FVector2D Position)
{
	Super::MoveToPosition(Position);
	bHasMoved = true;
}

TArray<FMove> UChessPawn::GetAvailableMoves()
{
	TArray<FVector2D> PossibleMoves = GetPossiblePositions();
	TArray<FMove> ValidPositions = MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(),this);
	TArray<FMove> AvailableMoves;

	for (const FMove ValidPosition : ValidPositions)
	{
		const bool bPositionsHaveSameX = ValidPosition.TargetPosition.X == BoardPosition.X;
		UChessPiece* TargetChessPiece = static_cast<UChessPiece*>(ValidPosition.TargetObject);
		if (TargetChessPiece)
		{
			if (!bPositionsHaveSameX && TargetChessPiece->GetColor() != Color)
			{
				AvailableMoves.Add(ValidPosition);
			}
		}
		else if (bPositionsHaveSameX)
		{
			AvailableMoves.Add(ValidPosition);
		}
	}
	return AvailableMoves;
}
