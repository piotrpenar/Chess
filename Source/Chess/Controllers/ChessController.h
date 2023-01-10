#pragma once

#include "CoreMinimal.h"
#include "ChessGameMode.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "ChessController.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor
{
	GENERATED_BODY()

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
	UChessSceneUtilities* ChessboardSceneUtilities;
	UPROPERTY()
	AChessGameMode* GameMode;
	UPROPERTY()
	AChessGameState* GameState;
	UPROPERTY(EditAnywhere)
	UChessData* ChessData;
	UPROPERTY(EditAnywhere)
	AActor* ChessBoardOrigin;
	
	void CreateChessboardSceneUtilities();
	void CreateChessHighlighter();
	void CreateChessboardController();
	void ChessFigureSelected(const AChessFigure* ChessFigure) const;
	void MoveSelected(const FMove Move) const;
	void ExecutePlayerMove(FMove Move) const;
	
protected:
	virtual void BeginPlay() override;
	
};
