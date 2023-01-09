#pragma once
#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "ChessMovesProvider.generated.h"

UINTERFACE()
class UChessMovesProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IChessMovesProvider
{
	GENERATED_BODY()

public:
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject);
};
