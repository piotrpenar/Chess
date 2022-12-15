#pragma once
#include "IntVectorTypes.h"
#include "Chess/ChessData.h"
#include "Chess/EColor.h"
#include "Chess/EFigureType.h"
#include "UChessPiece.generated.h"

UCLASS()
class UChessPiece : public UObject
{
	GENERATED_BODY()
public:
	UChessPiece Clone(const UChessPiece* SourceChessPiece);
	void SetColor(EColor PieceColor);
	void CreateActor(UChessData* ChessData) const;
	void SetPosition(int Row,int Column);
	void MoveToPosition();
	void GetAvailableMoves();

protected:
	EFigureType FigureType = EFigureType::Pawn;
	
private :
	UPROPERTY()
	FVector2D BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	UPROPERTY()
	AActor* ChessPieceActor;
	UPROPERTY()
	EColor Color = EColor::White;
	void SetActorPosition();
	void MoveActorToPosition();
};
