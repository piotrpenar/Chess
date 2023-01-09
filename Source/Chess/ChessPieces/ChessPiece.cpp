#include "ChessPiece.h"
#include "Figures/AChessFigure.h"


void UChessPiece::Initialize(const TScriptInterface<IMovementRulesProvider> SimulatedMovementRules,AChessFigure* ChessFigure)
{
	MovementRules = SimulatedMovementRules;
	ChessPieceActor = ChessFigure;
}

TArray<FMove> UChessPiece::GetAvailableMoves()
{
	return {};
}

void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

EColor UChessPiece::GetColor() const
{
	return Color;
}

EFigure UChessPiece::GetFigureType()
{
	return EFigure::Invalid;
}

FIntPoint UChessPiece::GetBoardPosition()
{
	return BoardPosition;
}

void UChessPiece::SetPosition(const FIntPoint Position)
{
	this->BoardPosition = Position;
	if (ChessPieceActor)
	{
		ChessPieceActor->SetBoardPosition(Position);
	}
}

void UChessPiece::MoveToPosition(const FIntPoint Position, const FVector ActorPosition)
{
	bHasMoved = true;
	BoardPosition = Position;
	if (ChessPieceActor)
	{
		ChessPieceActor->SetBoardPosition(Position);
		SetActorPosition(ActorPosition);
	}
}

bool UChessPiece::HasMoved() const
{
	return bHasMoved;
}

void UChessPiece::DestroyActor() const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->Destroy();
	}
}

void UChessPiece::SetActorRotation(const FRotator Rotation) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorRotation(Rotation);
	}
}

void UChessPiece::SetActorPosition(const FVector Position) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorLocation(Position);
	}
}

void UChessPiece::SetActorTransform(const FTransform Transform) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorTransform(Transform);
	}
}
