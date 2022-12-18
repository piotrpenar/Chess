﻿#include "ChessPiece.h"
#include "Figures/AChessFigure.h"

void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

void UChessPiece::CreateActor(UWorld* World)
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
	
	int value =static_cast<int>(this->GetFigureType());
	UE_LOG(LogTemp, Warning, TEXT("Figure type is %d"), value);
	
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
	Actor->SourcePiece = this;
}

void UChessPiece::SetPosition(const int Row, const int Column)
{
	this->BoardPosition = FVector2D(Row, Column);
}

void UChessPiece::MoveToPosition()
{
	
}

void  UChessPiece::SetActorRotation(const FRotator Rotation ) const
{
	ChessPieceActor->SetActorRotation(Rotation);
}

void UChessPiece::SetActorPosition(const FVector Position) const
{
	ChessPieceActor->SetActorLocation(Position);
}

// void UChessPiece::SetActorTransform(const FTransform Transform) const
// {
// 	ChessPieceActor->SetActorTransform(Transform);
// }

EColor UChessPiece::GetColor() const
{
	return Color;
}

TArray<FMove> UChessPiece::GetAvailableMoves() 
{
	return {};
}

//TODO: Change this to animation
void UChessPiece::MoveActorToPosition(const FVector Position)
{
	SetActorPosition(Position);
}