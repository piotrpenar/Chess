// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "UObject/Object.h"
#include "ChessRulesController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessRulesController : public UObject
{
	GENERATED_BODY()

public:
	TArray<UChessPiece*> GetAllPiecesOfColor(TArray<F2DBoardArray>* Array, EColor Color);
	UChessPiece* GetFigureFromArray(TArray<UChessPiece*> Array, EFigureType Figure);
	void CheckBoardStatus(TArray<F2DBoardArray>* Board);
	void CheckForMate(TArray<UChessPiece*> WhitePieces, UChessPiece* BlackKing);
	void CheckForCheckMate();
	UChessPiece* UChessRulesController::FindChessPiece(TArray<F2DBoardArray>* Board,EFigureType Figure,EColor Color);
};
