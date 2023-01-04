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
	UPROPERTY()
	UChessboardController* SimulatedController;
	UPROPERTY()
	UChessboard* SimulatedBoard;

	bool bIsSimulation = false;
public:

	void Initialize(UChessData* NewChessData,UChessboard* NewBoard,TScriptInterface<IChessGameState> NewChessGameState);
	void CreateChessboardSimulation();
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position);
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece) override;
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidSpecialMoves(UChessPawn* ChessPawn) override;
	UChessPiece* GetOtherPieceAtPosition(FIntPoint BoardPosition) const;
	void SetAsSimulation();
	
private:
	TArray<FMove> GetPawnSpecialMoves();
	TArray<FMove> GetKingSpecialMoves();
	
};

