﻿#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override { return EFigureType::Pawn;};

private:
	bool bHasMoved;
	virtual TArray<FMove> GetAvailableMoves() const override;
	virtual void MoveToPosition() override;
};
