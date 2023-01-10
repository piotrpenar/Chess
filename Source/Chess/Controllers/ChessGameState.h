#pragma once

#include "CoreMinimal.h"
#include "ChessRulesController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "GameFramework/GameState.h"
#include "ChessGameState.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessGameState final : public AGameState
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	UChessboardController* ChessboardController;
	UPROPERTY()
	EColor CurrentPlayer = EColor::White;
	
public:
	void CreateChessboard();
	UChessboard* GetChessboard() const;
	EColor GetCurrentPlayer() const;
	void SetCurrentPlayer(EColor Color);
};
