#include "ChessPawn.h"

#include "Chess/Helpers/ChessMovesHelper.h"


TArray<FMove> UChessPawn::GetAvailableMoves()
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
		PossibleMoves.Add(BoardPosition + FVector2D(0, Direction * 2));
	}

	for (const FVector2D PossibleMove : PossibleMoves)
	{
		if (!(ChessData->IsValidPosition(PossibleMove)))
		{
			UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"), *FString(CurrentTargetPosition.ToString()),
			       *FString(PossibleMove.ToString()))
			continue;
		}
		UChessPiece* TargetObject = UChessMovesHelper::GetOtherPieceAtPosition(
			FChessMovesData(PossibleMoves, BoardProvider, Color, BoardPosition), PossibleMove);
		const bool bIsSameX = PossibleMove.X == BoardPosition.X;
		if (TargetObject)
		{
			if (!bIsSameX && TargetObject->GetColor() != Color)
			{
				ValidMoves.Add(FMove(PossibleMove, TargetObject));
			}
		}
		else if (bIsSameX)
		{
			ValidMoves.Add(FMove(PossibleMove, TargetObject));
		}
	}
	return ValidMoves;
}

void UChessPawn::MoveToPosition(FVector2D Position)
{
	Super::MoveToPosition(Position);
	bHasMoved = true;
}
