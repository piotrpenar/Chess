#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessKing.generated.h"

UCLASS()
class UChessKing final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves()  override;
};
