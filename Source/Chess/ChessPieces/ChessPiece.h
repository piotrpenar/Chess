#pragma once
#include "IntVectorTypes.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "ChessPiece.generated.h"

UCLASS()
class UChessPiece : public UObject
{
	GENERATED_BODY()
public:
	void SetColor(EColor PieceColor);
	void CreateActor(UChessData* ChessData, UWorld* World,EFigureType Figure);
	void SetPosition(int Row,int Column);
	void MoveToPosition();
	void GetAvailableMoves();
	void SetActorTransform(FTransform Transform) const;
	virtual EFigureType GetFigureType() { return EFigureType::Pawn;};
	
private :
	
	UPROPERTY(EditDefaultsOnly,Category="ActorSpawning")
	TSubclassOf<AChessFigure> UsefulActorBP;
	UPROPERTY()
	FVector2D BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	UPROPERTY()
	AActor* ChessPieceActor;
	UPROPERTY()
	EColor Color = EColor::White;
	void SetActorPosition(FVector Position) const;
	void SetActorRotation(FRotator Rotation) const;
	void MoveActorToPosition(FVector Position);
};
