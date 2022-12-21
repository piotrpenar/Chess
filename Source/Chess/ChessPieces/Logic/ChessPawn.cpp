#include "ChessPawn.h"

#include "Chess/Helpers/ChessMovesHelper.h"


EFigureType UChessPawn::GetFigureType()
{
	return EFigureType::Pawn;
}

TArray<FVector2D> UChessPawn::GetPossibleMoves()
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

FChessMovesData UChessPawn::GenerateMovesData()
{
	return FChessMovesData(GetPossibleMoves(), BoardProvider, Color, BoardPosition,this);
}

void UChessPawn::MoveToPosition(FVector2D Position)
{
	Super::MoveToPosition(Position);
	bHasMoved = true;
}

TArray<FMove> UChessPawn::GetAvailableMoves()
{
	TArray<FVector2D> PossibleMoves = GetPossibleMoves();
	const FChessMovesData MovesData = GenerateMovesData();
	TArray<FMove> ValidMoves;

	for (const FVector2D PossibleMove : PossibleMoves)
	{
		if (!(BoardProvider->IsValidMove(PossibleMove, this)))
		{
			//UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"), *FString(CurrentTargetPosition.ToString()),*FString(PossibleMove.ToString()))
			continue;
		}
		UChessPiece* TargetObject = UChessMovesHelper::GetOtherPieceAtPosition(MovesData, PossibleMove);
		const bool bPositionsHaveSameX = PossibleMove.X == BoardPosition.X;
		if (TargetObject)
		{
			if (!bPositionsHaveSameX && TargetObject->GetColor() != Color)
			{
				ValidMoves.Add(FMove(PossibleMove, TargetObject));
			}
		}
		else if (bPositionsHaveSameX)
		{
			ValidMoves.Add(FMove(PossibleMove, TargetObject));
		}
	}
	return ValidMoves;
}
