#pragma once
#include "CoreMinimal.h"
#include "ChessboardMovementRules.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/TurnsProvider.h"
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
	UChessSceneUtilities* ChessboardTransformUtilities;
	UPROPERTY()
	TScriptInterface<ITurnsProvider> ChessGameState;
	
	void InitializeChessboard(TFunction<void(AChessFigure*)> FigureClickedCallback);
	void CreateSimulatedChessboard();
	void FinishChessboardsInitialization() const;
	void AddChessPieceAtPosition(UChessPiece* ChessPiece, const FIntPoint Position) const;
	void RemoveChessPieceAtPosition(FIntPoint Position) const;
	void HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const;
	void HandleEnPassant(UChessPiece* ChessPiece) const;
	void PromotePawn(UChessPiece* ChessPiece, EFigure TargetFigure) const;
	void HandlePawnPromotion(const FMove& Move) const;

public:
	void Initialize(UChessSceneUtilities* ChessSceneUtilitiesReference, UChessData* NewChessData, TFunction<void(AChessFigure*)> FigureClickedCallback);
	void ResetChessboard() const;
	void MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position) const;
	void HandleSpecialMoveType(const FMove& Move) const;
	void SetupPiecesCallbacks(ITurnsProvider* TurnsProvider) const;
	TScriptInterface<IMovementRulesProvider> GetChessboardMovementRuleProvider() const;
};
