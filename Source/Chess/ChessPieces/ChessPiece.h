#pragma once
#include "IntVectorTypes.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "Chess/Utils/FMove.h"
#include "Interfaces/MovesProvider.h"
#include "ChessPiece.generated.h"

UCLASS()
class UChessPiece : public UObject, public IMovesProvider
{
	GENERATED_BODY()
public:
	void SetColor(EColor PieceColor);
	void CreateActor(UWorld* World,EFigureType Figure);
	void SetPosition(int Row,int Column);
	virtual void MoveToPosition();
	void SetActorTransform(FTransform Transform) const;
	
	virtual EFigureType GetFigureType()  { return EFigureType::Pawn;}
	EColor GetColor() const;
	virtual TArray<FMove> GetAvailableMoves() const;
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TArray<F2DBoardArray> Board;

protected:
	
	UPROPERTY()
	EColor Color = EColor::White;
	UPROPERTY()
	FVector2D BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	
private :
	UPROPERTY()
	AActor* ChessPieceActor;
	void SetActorPosition(FVector Position) const;
	void SetActorRotation(FRotator Rotation) const;
	void MoveActorToPosition(FVector Position);
};
