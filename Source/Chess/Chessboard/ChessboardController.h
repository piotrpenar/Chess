#pragma once
#include "CoreMinimal.h"
#include "ChessboardMovementRules.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Data/ChessData.h"
#include "ChessboardController.generated.h"

UCLASS()
class CHESS_API UChessboardController final : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	UChessboardMovementRules* ChessboardMovementRules;
	UPROPERTY()
	USimulatedChessboard* SimulatedBoard;
	UPROPERTY()
	UChessboardMovementRulesBase* SimulationMovementRules;
	
	UPROPERTY()
	TScriptInterface<ITurnsProvider> ChessGameState;

	bool bIsSimulation = false;
public:
	void Initialize(UChessData* NewChessData, AActor* ChessBoardOrigin, TFunction<void(AChessFigure*)> FigureClickedCallback);
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position) const;
	void HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const;
	void HandleEnPassant(UChessPiece* ChessPiece) const;
	void PromotePawn(UChessPiece* ChessPiece, EFigure TargetFigure) const;
	void HandlePawnPromotion(const FMove& Move) const;
	void HandleSpecialMoveType(const FMove& Move) const;
	void RemoveChessPieceAtPosition(FIntPoint Position) const;
	void AddChessPieceAtPosition(UChessPiece* ChessPiece, const FIntPoint Position) const;
	IMovementRulesProvider* GetChessboardMovementRuleProvider();
};
