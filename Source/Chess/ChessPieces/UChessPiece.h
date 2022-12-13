#pragma once
#include "IntVectorTypes.h"
#include "Chess/EColor.h"
#include "UChessPiece.generated.h"

UCLASS()
class UChessPiece : public UObject
{
	GENERATED_BODY()
public:
	UChessPiece Clone(const UChessPiece* SourceChessPiece);
	void SetColor(EColor Color);
	void CreateActor();
	void SetPosition(int Row,int Column);
	void MoveToPosition();
	void GetAvailableMoves();

private :
	UE::Geometry::FVector2i BoardPosition;
	FVector3f WorldPosition;
	AActor ChessPieceActor;
	EColor Color = EColor::White;
	void SetActorPosition();
	void MoveActorToPosition();
};
