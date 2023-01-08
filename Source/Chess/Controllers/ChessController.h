// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChessboardController.h"
#include "ChessRulesController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Controllers/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/BoardHighlighter.h"
#include "Chess/Interfaces/ChessGameState.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigure.h"
#include "ChessController.generated.h"

/**
 * 
*/
UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor , public IBoardHighlighter, public IChessGameState
{
	GENERATED_BODY()

public:
	void GenerateChessPieces(const EColor FigureColor);
	void SetupChessPiece( UChessPiece* ChessPiece,EColor Color, int X, int Y);
	UChessPiece* GenerateChessPiece(const EFigure Figure);
	virtual void BeginPlay() override;
	virtual void EndTurn() override;
	virtual void CreateHighlights(TArray<FMove> Moves) override;
	virtual void SetSelectedFigure(AActor* Figure) override;
	void HandleCastling(const FMove& Move, UChessPiece* ChessPiece);
	void HandleEnPassant(UChessPiece* ChessPiece);
	void PromotePawn(UChessPiece* Object, EFigure Queen);
	void HandlePawnPromotion(const FMove& Move);
	void HandleSpecialMoveType(const FMove& Move);
	virtual void HighlightSelected(AActor* Source) override;
	virtual EColor GetCurrentPlayer() override;
	void ClearHighlights();
	
	DECLARE_DERIVED_EVENT( AChessController, IChessGameState::FTurnEnded, FTurnEnded);
	virtual FTurnEnded& OnTurnEnded() override;
	FTurnEnded TurnEndedEvent;

	UPROPERTY(EditAnywhere)
	UChessData* ChessData;
	
	UPROPERTY(EditAnywhere)
	AActor* ChessBoardOrigin;
	
	
private:

	UPROPERTY()
	UChessRulesController* RulesController;
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	UChessboardController* ChessboardController;
	UPROPERTY()
	TMap<EFigure, UChessPiece*> FigureTypeMap;
	UPROPERTY()
	TArray<AActor*> CurrentHighlights;
	UPROPERTY()
	AChessFigure* CurrentSelectedFigure;
	
	EColor CurrentPlayer = EColor::White;
	
	FTransform GenerateChessPieceTransform(int TargetRow, int TargetColumn, EColor Color);
	void GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int Y);
	void BroadcastTurnEnded(EColor Color);
	
	const TArray<EFigure> Pawns = {
		EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn,
		EFigure::Pawn, EFigure::Pawn
	};
	const TArray<EFigure> Men = {
		EFigure::Rook, EFigure::Knight, EFigure::Bishop, EFigure::King, EFigure::Queen, EFigure::Bishop,
		EFigure::Knight, EFigure::Rook
	};
	
};
