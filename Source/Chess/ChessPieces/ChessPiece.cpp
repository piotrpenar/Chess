#include "ChessPiece.h"
#include "Figures/AChessFigure.h"


void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

void UChessPiece::CreateActor(UChessData* ChessData, UWorld* World,EFigureType FigureType)
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
	UStaticMesh* Mesh = ChessData->GetMeshForType(FigureType);
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
}

void UChessPiece::SetPosition(const int Row, const int Column)
{
	this->BoardPosition = FVector2D(Row, Column);
}

void UChessPiece::MoveToPosition()
{
	
}

void UChessPiece::GetAvailableMoves()
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

void UChessPiece::SetActorTransform(const FTransform Transform) const
{
	ChessPieceActor->SetActorTransform(Transform);
}

//TODO: Change this to animation
void UChessPiece::MoveActorToPosition(const FVector Position)
{
	SetActorPosition(Position);
}
