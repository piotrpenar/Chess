#pragma once

#include "CoreMinimal.h"
#include "ChessHighlighter.h"
#include "ChessRulesController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "ChessController.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor
{
	GENERATED_BODY()
public:
	void GenerateChessPieces(const EColor FigureColor);
	void SetupChessPiece(UChessPiece* ChessPiece, EColor Color, int X, int Y);
	UChessPiece* GenerateChessPiece(const EFigure Figure);
	virtual void BeginPlay() override;
	void HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const;
	void HandleEnPassant(UChessPiece* ChessPiece) const;
	void PromotePawn(UChessPiece* ChessPiece, EFigure TargetFigure);
	void HandlePawnPromotion(const FMove& Move);
	void HandleSpecialMoveType(const FMove& Move);

	UPROPERTY(EditAnywhere)
	UChessData* ChessData;

	UPROPERTY(EditAnywhere)
	AActor* ChessBoardOrigin;
	
private:
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
	UPROPERTY()
	TScriptInterface<IChessMovesHighlighter> Highlighter;

	FTransform GenerateChessPieceTransform(int TargetRow, int TargetColumn, EColor Color) const;
	void GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int Y);
};
