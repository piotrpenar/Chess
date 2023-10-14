#pragma once
#include "CoreMinimal.h"
#include "Chess/Enums/Color.h"
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
	DECLARE_EVENT_OneParam(ITurnsProvider, FTurnEnded, EColor);
	
	virtual void EndTurn();
	virtual FTurnEnded& OnTurnEnded(EColor Color) = 0;
};
