#pragma once
#include "Chess/Utils/ChessMovesData.h"
#include "Chess/ChessPieces/ChessPiece.h"

#include "ChessMovesHelper.generated.h"

UCLASS()
class UChessMovesHelper final : public UObject
{
	GENERATED_BODY()
public:
	static TArray<FMove> GetValidMovesFromPositions(FChessMovesData MovesData, const UChessData* ChessData);
	static TArray<FMove> GetValidMovesFromDirections(FChessMovesData MovesData, UChessData* ChessData);
	static UChessPiece* GetOtherPieceAtPosition(FChessMovesData MovesData, FVector2D BoardPosition);
};
