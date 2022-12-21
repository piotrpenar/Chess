﻿#include "ChessPiece.h"

#include "Chess/Utils/F2DBoardArray.h"
#include "Figures/AChessFigure.h"

void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

EFigure UChessPiece::GetFigureType()
{
	return EFigure::Invalid;
}

FVector2D UChessPiece::GetBoardPosition() const
{
	return BoardPosition;
}

bool UChessPiece::CanMoveThisTurn()
{
	return ChessGameState->GetCurrentPlayer() == Color;
}

EColor UChessPiece::GetColor() const
{
	return Color;
}

TArray<FMove> UChessPiece::GetAvailableMoves() 
{
	return {};
}

void UChessPiece::DestroyChessPiece() const
{
	ChessPieceActor->Destroy();
}

void UChessPiece::SetPosition(const int X,const int Y)
{
	this->BoardPosition = FVector2D(X, Y);
}

void  UChessPiece::SetActorRotation(const FRotator Rotation ) const
{
	ChessPieceActor->SetActorRotation(Rotation);
}

void UChessPiece::SetActorPosition(const FVector Position) const
{
	ChessPieceActor->SetActorLocation(Position);
}

void UChessPiece::SetActorTransform(const FTransform Transform) const
{
	ChessPieceActor->SetActorTransform(Transform);
}

void UChessPiece::MoveToPosition(FVector2D Position)
{
	const FVector2D PreviousPosition = FVector2D(BoardPosition);
	BoardPosition = Position;
	BoardProvider->SetPieceAtPosition(Position,this);
	MoveActorToPosition(Position);
	BoardProvider->SetPieceAtPosition(PreviousPosition,nullptr);
	ChessGameState->EndTurn();
}

void UChessPiece::CreateActor(UWorld* World,IBoardHighlighter* Highlighter)
{
	if(!IsValid(World))
	{
		UE_LOG(LogTemp,Log,TEXT("World is invalid"))
		return;
	}
	AChessFigure* Actor = World->SpawnActor<AChessFigure>(ChessData->GetChessFigureActor());
	if(!IsValid(Actor))
	{
		UE_LOG(LogTemp,Log,TEXT("Actor is invalid"))
		return;
	}
	UActorComponent* Component = Actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	if(!IsValid(Component))
	{
		UE_LOG(LogTemp,Log,TEXT("Component is invalid"))
		return;
	}
	if(!IsValid(ChessData))
	{
		UE_LOG(LogTemp,Log,TEXT("ChessData is invalid"))
		return;
	}
	
	UStaticMesh* Mesh = ChessData->GetMeshForType(GetFigureType());
	if(!IsValid(Mesh))
	{
		UE_LOG(LogTemp,Log,TEXT("Mesh is invalid"))
		return;
	}
	UStaticMeshComponent* StaticMeshComponent = static_cast<UStaticMeshComponent*>(Component);
	if(!IsValid(StaticMeshComponent))
	{
		UE_LOG(LogTemp,Log,TEXT("StaticMeshComponent is invalid"))
		return;
	}
	StaticMeshComponent->SetStaticMesh(Mesh);
	ChessPieceActor = Actor;
	Actor->Highlighter = Highlighter;
	Actor->SourcePiece = this;
}

//TODO: Change this to animation
void UChessPiece::MoveActorToPosition(FVector2D Position) const
{
	SetActorPosition(BoardProvider->BoardToWorldTransform(Position.X,Position.Y).GetLocation());
}