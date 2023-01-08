#include "ChessPawn.h"

EFigure UChessPawn::GetFigureType()
{
	return EFigure::Pawn;
}

TArray<FIntPoint> UChessPawn::GetPossiblePositions() const
{
	const bool bIsWhite = Color == EColor::White;
	const int Direction = bIsWhite ? 1 : -1;
	TArray PossibleMoves = {
		BoardPosition + FIntPoint(-1, Direction),
		BoardPosition + FIntPoint(0, Direction),
		BoardPosition + FIntPoint(1, Direction),
	};
	return PossibleMoves;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UChessPawn::HandleTurnEnded(EColor& CurrentColor)
{
	UE_LOG(LogTemp, Log, TEXT("Subscription called!"))
	if (!IsValid(this))
	{
		return;
	}
	if (CurrentColor != Color)
	{
		bHasDoubleMoved = false;
	}
}

bool UChessPawn::HasDoubleMoved(const FIntPoint Position) const
{
	const FIntPoint PreviousPosition = BoardPosition;
	return abs(PreviousPosition.Y - Position.Y) == 2;
}

void UChessPawn::MoveToPosition(const FIntPoint Position, const FVector ActorPosition)
{
	if (HasDoubleMoved(Position))
	{
		bHasDoubleMoved = true;
		ChessGameState->OnTurnEnded().AddUObject(this, &UChessPawn::HandleTurnEnded);
	}
	Super::MoveToPosition(Position, ActorPosition);
}

bool UChessPawn::IsValidPassantTarget() const
{
	return bHasDoubleMoved;
}

TArray<FMove> UChessPawn::GetAvailableMoves()
{
	TArray<FIntPoint> PossibleMoves = GetPossiblePositions();
	TArray<FMove> ValidPositions = MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(), this);
	const TArray<FMove> SpecialMoves = MovementVerifier->GetValidSpecialMoves(this);
	TArray<FMove> AvailableMoves = SpecialMoves;

	for (const FMove ValidPosition : ValidPositions)
	{
		const bool bPositionsHaveSameX = ValidPosition.TargetPosition.X == BoardPosition.X;
		const UChessPiece* TargetChessPiece = static_cast<UChessPiece*>(ValidPosition.TargetObject);
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
