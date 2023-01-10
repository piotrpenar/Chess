#pragma once
#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "MovementRulesProvider.generated.h"

UINTERFACE()
class UMovementRulesProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IMovementRulesProvider
{
	GENERATED_BODY()

public:
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromPositions(const TArray<FIntPoint>& Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromDirections(const TArray<FIntPoint>& Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject);
};
