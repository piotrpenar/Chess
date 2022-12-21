#pragma once
#include "Chess/Utils/ChessMovesData.h"
#include "Chess/ChessPieces/ChessPiece.h"

#include "ChessMovesHelper.generated.h"

UCLASS()
class UChessMovesHelper final : public UObject
{
	GENERATED_BODY()
public:
	static TArray<FMove> GetValidMovesFromPositions(FChessMovesData MovesData);
	static TArray<FMove> GetValidMovesFromDirections(FChessMovesData MovesData);
	static UChessPiece* GetOtherPieceAtPosition(FChessMovesData MovesData, FVector2D BoardPosition);
};
