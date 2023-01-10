#pragma once
#include "CoreMinimal.h"
#include "Chess/Enums/EColor.h"
#include "TurnsProvider.generated.h"

UINTERFACE()
class UTurnsProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API ITurnsProvider
{
	GENERATED_BODY()

public:
	virtual void EndTurn();
	DECLARE_EVENT_OneParam(IChessGameState, FTurnEnded, EColor);

	virtual FTurnEnded& OnTurnEnded() = 0;
};
