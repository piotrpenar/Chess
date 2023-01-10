#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessRook.generated.h"

UCLASS()
class CHESS_API UChessRook final : public UChessPiece
{
	GENERATED_BODY()

	TArray<FIntPoint> GetPossibleDirections() const;

public:
	virtual EFigure GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves() override;
};
