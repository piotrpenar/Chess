// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessboardBase.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Interfaces/MovementRulesProvider.h"
#include "UObject/Object.h"
#include "ChessboardMovementRulesBase.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessboardMovementRulesBase : public UObject, public IMovementRulesProvider
{
	GENERATED_BODY()
protected:	
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	UChessboardBase* Chessboard;
	
public:
	virtual void InitializeMovementRules(UChessData* ChessDataReference,UChessboardBase* ChessboardReference);
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject) override;
	
private:
	TArray<FMove> GetPawnSpecialMoves(UChessPiece* ChessPiece);
	TArray<FMove> GetKingSpecialMoves(UChessPiece* KingPiece);
	bool CanPawnDoubleMove(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);
	TArray<FMove> GetEnPassantMoves(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);\
	void AdjustMoveType(FMove* Move) const;
};

