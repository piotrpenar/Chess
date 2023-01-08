#pragma once
#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "MovementVerifier.generated.h"

UINTERFACE()
class UMovementVerifier : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IMovementVerifier
{
	GENERATED_BODY()

public:
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject);
};
