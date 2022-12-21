#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/ChessMovesData.h"
#include "ChessKing.generated.h"

UCLASS()
class UChessKing final : public UChessPiece
{
	GENERATED_BODY()
	
	FChessMovesData GenerateMovesData();
	TArray<FVector2D> GetPossibleMoves() const;
	
public:
	virtual EFigure GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves()  override;
};
