#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "ChessController.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void ChessFigureSelected(const AChessFigure* ChessFigure) const;
	void HighlightSelected(const FMove* BoardHighlight) const;
	void ExecutePlayerMove(FMove Move) const;

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
	UPROPERTY()
	UChessSceneUtilities* ChessboardTransformUtilities;
};
