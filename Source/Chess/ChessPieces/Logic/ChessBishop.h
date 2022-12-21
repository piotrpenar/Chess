﻿#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessBishop.generated.h"

UCLASS()
class UChessBishop final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves()  override;
};
