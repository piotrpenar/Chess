// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/MovementVerifier.h"
#include "UObject/Object.h"
#include "ChessboardController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessboardController : public UObject, public IMovementVerifier
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	TScriptInterface<IChessGameState> ChessGameState;
public:

	void SetBoard(UChessboard* NewBoard);
	void SetChessData(UChessData* NewChessData);
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FVector2D Position);
	virtual bool IsValidMove(const FVector2D Position, UObject* ChessPiece) override;
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FVector2D> Directions, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FVector2D> Directions, UObject* ChessPieceObject) override;
	UChessPiece* GetOtherPieceAtPosition(FVector2D BoardPosition) const;
	void MoveActorToPosition(FVector2D Position, UChessPiece* ChessPiece) const;
};
