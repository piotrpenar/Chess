#pragma once

#include "CoreMinimal.h"
#include "GameRoundController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/Figure.h"
#include "Chess/Global/ChessGameMode.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "Chess/Interfaces/MoveExecutor.h"
#include "ChessController.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessController final : public AActor, public IMoveExecutor
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
	UPROPERTY()
	UGameRoundController* GameRoundController;
	
	void CreateChessboardSceneUtilities();
	void CreateChessHighlighter();
	void CreateChessboardController();
	void ChessFigureSelected(const AChessFigure* ChessFigure) const;
	void MoveSelected(const FMove Move) const;
	
protected:
	void SetupGameRoundController();
	virtual void BeginPlay() override;

public:
	virtual void ExecutePlayerMove(FMove Move) const override;
	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn(int Index) const;
	UFUNCTION(BlueprintCallable)
	void ResetChessGame() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FPieceCaptured, enum EColor, Color, EFigure, Figure );
	
	UPROPERTY(BlueprintAssignable, Category = "Chess")
	FPieceCaptured OnPieceCaptured;

};
