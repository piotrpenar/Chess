#pragma once
#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/MovementVerifier.h"
#include "ChessboardController.generated.h"

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
	void Initialize(UChessData* NewChessData, UChessboard* NewBoard, TScriptInterface<IChessGameState> NewChessGameState);
	void CreateChessboardSimulation();
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position);
	void RemoveChessPieceAtPosition(FIntPoint Position);
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece) override;
	void AdjustMoveType(FMove* Move);
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject) override;
	UChessPiece* GetPieceAtPosition(FIntPoint BoardPosition) const;
	void SetAsSimulation();
	void AddChessPieceAtPosition(UChessPiece* NewFigure, const FIntPoint Position);

private:
	TArray<FMove> GetPawnSpecialMoves(UChessPiece* Pawn);
	TArray<UChessPiece*> GetChessPiecesOfType(EColor Color, EFigure FigureType);
	TArray<FMove> GetKingSpecialMoves(UChessPiece* King);
	bool CanPawnDoubleMove(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);
	TArray<FMove> GetEnPassantMoves(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);
};
