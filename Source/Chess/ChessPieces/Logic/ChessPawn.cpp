#include "ChessPawn.h"


EFigure UChessPawn::GetFigureType()
{
	return EFigure::Pawn;
}

TArray<FIntPoint> UChessPawn::GetPossiblePositions()
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

void UChessPawn::HandleTurnEnded(EColor& CurrentColor)
{
	UE_LOG(LogTemp, Log, TEXT("Subscription called!"))
	if (!IsValid(this))
	{
		return;
	}
	if(CurrentColor != Color)
	{
		bHasDoubleMoved = false;
	}
}

bool UChessPawn::HasDoubleMoved(const FIntPoint Position) const
{
	const FIntPoint PreviousPosition = BoardPosition;
	return abs(PreviousPosition.Y - Position.Y) == 2;
}

void UChessPawn::MoveToPosition(FIntPoint Position, FVector ActorPosition)
{
	if(HasDoubleMoved(Position))
	{
		bHasDoubleMoved = true;
		UE_LOG(LogTemp, Log, TEXT("Subscribing for event!"))
		ChessGameState->OnTurnEnded().AddUObject(this,&UChessPawn::HandleTurnEnded);
	}
	Super::MoveToPosition(Position,ActorPosition);
	bHasMoved = true;
}

bool UChessPawn::IsValidPassantTarget()
{
	return bHasDoubleMoved;
}

bool UChessPawn::HasMoved()
{
	return bHasMoved;
}

TArray<FMove> UChessPawn::GetAvailableMoves()
{
	TArray<FIntPoint> PossibleMoves = GetPossiblePositions();
	TArray<FMove> ValidPositions = MovementVerifier->GetValidMovesFromPositions(GetPossiblePositions(),this);
	TArray<FMove> SpecialMoves = MovementVerifier->GetValidSpecialMoves(this);
	TArray<FMove> AvailableMoves = SpecialMoves;

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
