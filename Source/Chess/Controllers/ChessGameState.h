#pragma once

#include "CoreMinimal.h"
#include "ChessRulesController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "GameFramework/GameState.h"
#include "ChessGameState.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessGameState final : public AGameState, public ITurnsProvider
{
	GENERATED_BODY()
	
	virtual void EndTurn() override;
	virtual EColor GetCurrentPlayer() override;

	DECLARE_DERIVED_EVENT(AChessGameState, ITurnsProvider::FTurnEnded, FTurnEnded);
	virtual FTurnEnded& OnTurnEnded() override;
	FTurnEnded TurnEndedEvent;
	void Initialize();
	void BroadcastTurnEnded(EColor Color) const;
	EColor CurrentPlayer = EColor::White;
	
	UPROPERTY()
	UChessRulesController* RulesController;
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	UChessboardController* ChessboardController;
};
