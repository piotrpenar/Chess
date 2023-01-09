#pragma once
#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/ChessMovesProvider.h"
#include "ChessboardController.generated.h"

UCLASS()
class CHESS_API UChessboardController final : public UObject, public IChessMovesProvider
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	TScriptInterface<ITurnsProvider> ChessGameState;
	UPROPERTY()
	UChessboardController* SimulatedController;
	UPROPERTY()
	UChessboard* SimulatedBoard;

	bool bIsSimulation = false;
public:
	void Initialize(UChessData* NewChessData, UChessboard* NewBoard, TScriptInterface<ITurnsProvider> NewChessGameState);
	void CreateChessboardSimulation();
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position) const;
	void RemoveChessPieceAtPosition(FIntPoint Position) const;
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPiece) override;
	void AdjustMoveType(FMove* Move) const;
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject) override;
	virtual TArray<FMove> GetValidSpecialMoves(UObject* ChessPieceObject) override;
	UChessPiece* GetPieceAtPosition(FIntPoint BoardPosition) const;
	void SetAsSimulation();
	void AddChessPieceAtPosition(UChessPiece* NewFigure, const FIntPoint Position);

private:
	TArray<FMove> GetPawnSpecialMoves(UChessPiece* ChessPiece);
	TArray<UChessPiece*> GetChessPiecesOfType(EColor Color, EFigure FigureType) const;
	TArray<FMove> GetKingSpecialMoves(UChessPiece* KingPiece);
	bool CanPawnDoubleMove(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);
	TArray<FMove> GetEnPassantMoves(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction);
};
