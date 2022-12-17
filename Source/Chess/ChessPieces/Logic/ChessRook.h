﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessRook.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessRook final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override { return EFigureType::Rook;};
	virtual TArray<FMove> GetAvailableMoves() const override;
};
