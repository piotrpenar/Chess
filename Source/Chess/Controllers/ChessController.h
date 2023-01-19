#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Global/ChessGameMode.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "ChessController.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UChessboardController* ChessboardController;
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
	UPROPERTY(EditAnywhere)
	APawn* FirstPlayerPawn;
	UPROPERTY(EditAnywhere)
	APawn* SecondPlayerPawn;
	
	void CreateChessboardSceneUtilities();
	void CreateChessHighlighter();
	void CreateChessboardController();
	void ChessFigureSelected(const AChessFigure* ChessFigure) const;
	void MoveSelected(const FMove Move) const;
	void ExecutePlayerMove(FMove Move) const;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn(int Index) const;
	UFUNCTION(BlueprintCallable)
	void ResetChessGame() const;
	
};
