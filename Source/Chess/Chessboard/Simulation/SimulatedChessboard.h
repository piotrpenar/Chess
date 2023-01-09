// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessboardBase.h"
#include "SimulatedChessboard.generated.h"

UCLASS()
class CHESS_API USimulatedChessboard final : public UChessboardBase
{
	GENERATED_BODY()
	
public:
	UChessPiece* CreateSimulatedChessPiece(UChessPiece* ChessPiece);
	void InitializeSimulatedBoard(UChessboardBase* OriginalBoard);
};
