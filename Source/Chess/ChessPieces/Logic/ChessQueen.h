#pragma once
#include "Chess/ChessPieces/ChessPiece.h"

#include "ChessQueen.generated.h"

UCLASS()
class UChessQueen final : public UChessPiece
{
	GENERATED_BODY()
	
	TArray<FIntPoint> GetPossibleDirections() const;
public:
	virtual EFigure GetFigureType() override;
	virtual TArray<FMove> GetAvailableMoves() override;
};
