#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessKnight.generated.h"

UCLASS()
class UChessKnight final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override { return EFigureType::Knight;};
	virtual TArray<FMove> GetAvailableMoves() const override;
};
