#pragma once
#include "CoreMinimal.h"
#include "Chess/Utils/EColor.h"
#include "ChessGameState.generated.h"

UINTERFACE()
class UChessGameState : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IChessGameState
{
	GENERATED_BODY()

public:
	virtual EColor GetCurrentPlayer();
	virtual void EndTurn();
	
	DECLARE_EVENT_OneParam(IChessGameState, FTurnEnded, EColor&);
	virtual FTurnEnded& OnTurnEnded() = 0;
};
