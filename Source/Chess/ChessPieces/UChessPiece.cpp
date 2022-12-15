#include "UChessPiece.h"

#include "AChessFigure.h"


void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

void UChessPiece::CreateActor(UChessData* ChessData) const
{
	const AChessFigure* Actor = GetWorld()->SpawnActor<AChessFigure>(AChessFigure::StaticClass());
	UActorComponent* Component = Actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	static_cast<UStaticMeshComponent*>(Component)->SetStaticMesh(ChessData->GetMeshForType(FigureType));
}

void UChessPiece::SetPosition(const int Row, const int Column)
{
	this->BoardPosition = FVector2D(Row, Column);
}
