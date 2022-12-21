#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessKnight.generated.h"

UCLASS()
class UChessKnight final : public UChessPiece
{
	GENERATED_BODY()
	
	FChessMovesData GenerateMovesData();
	TArray<FVector2D> GetPossibleMoves();
	
public:
	virtual EFigure GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves()  override;
};
