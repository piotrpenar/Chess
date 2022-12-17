#pragma once
#include "IntVectorTypes.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/FMove.h"
#include "Logic/ChessPawn.h"
#include "ChessPiece.generated.h"

struct F2DBoardArray;
UCLASS()
class UChessPiece : public UObject
{
	GENERATED_BODY()
public:
	void SetColor(EColor PieceColor);
	void CreateActor(UChessData* ChessData, UWorld* World,EFigureType Figure);
	void SetPosition(int Row,int Column);
	virtual void MoveToPosition();
	void SetActorTransform(FTransform Transform) const;
	virtual EFigureType GetFigureType() { return EFigureType::Pawn;}
	EColor GetColor() const;
	virtual TArray<FMove> GetAvailableMoves() const;
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TArray<F2DBoardArray>* Board;

protected:
	
	UPROPERTY()
	EColor Color = EColor::White;
	UPROPERTY()
	FVector2D BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	UChessPiece* GetOtherPieceAtPosition(FVector2D BoardPosition) const;
	
private :
	UPROPERTY()
	AActor* ChessPieceActor;
	void SetActorPosition(FVector Position) const;
	void SetActorRotation(FRotator Rotation) const;
	void MoveActorToPosition(FVector Position);
};
