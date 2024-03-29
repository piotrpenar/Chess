﻿#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessKnight.generated.h"

UCLASS()
class UChessKnight final : public UChessPiece
{
	GENERATED_BODY()

	TArray<FIntPoint> GetPossiblePositions();

public:
	virtual EFigure GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves() override;
};
