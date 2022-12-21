﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/ECheckmateStatus.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "UObject/Object.h"
#include "ChessRulesController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessRulesController final : public UObject
{
	GENERATED_BODY()

	struct FEnemyMove
	{
		FMove Move;
		UChessPiece* Enemy;
	};

	static TArray<FEnemyMove> GetEnemiesAvailableMoves(TArray<UChessPiece*> EnemyPieces);
	static TArray<UChessPiece*> GetThreateningEnemies(TArray<FEnemyMove> EnemyMoves, UChessPiece* King);
	static ECheckmateStatus CalculateCheckmateStatus(TArray<UChessPiece*> EnemyPieces, TArray<UChessPiece*> AllyPieces, IChessBoardProvider* ChessBoardProvider);
	static UChessPiece* GetFigureFromArray(const TArray<UChessPiece*>& Array, const EFigure Figure);
	static bool IsKingAbleToEscape(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AlliedKing);
	static bool CanAllyCoverAnyEnemyMove(TArray<FEnemyMove> EnemyAvailableMoves, FMove AllyMove);
	static bool CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, FMove AllyMove, IChessBoardProvider* ChessBoardProvider);
	static bool CanAllyEliminateCheck(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AllyPiece, IChessBoardProvider* ChessBoardProvider);
	
public:
	ECheckmateStatus GetBoardStatusForColor(IChessBoardProvider* ChessBoardProvider, EColor Color);
};
