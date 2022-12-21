// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/ECheckMateStatus.h"
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
	ECheckMateStatus GetBoardStatus(TArray<F2DBoardArray>* Board,IChessBoardProvider* ChessBoardProvider);
	UChessPiece* FindChessPiece(TArray<F2DBoardArray>* Board,EFigureType Figure,EColor Color);
	bool AreMovePositionsEqual(FMove First, FMove Second);
	ECheckMateStatus CheckForCheckMate(TArray<UChessPiece*> EnemyPieces,TArray<UChessPiece*> AllyPieces, UChessPiece* King,IChessBoardProvider* ChessBoardProvider);
};
