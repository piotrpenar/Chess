#pragma once
#include "CoreMinimal.h"
#include "Chess/Enums/Color.h"
#include "TurnsProvider.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnEndedForPlayerEvent, EColor,Color);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEndedEvent);

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
	virtual FTurnEndedForPlayerEvent& OnTurnEndedForPlayerEvent() = 0;
	virtual FTurnEndedEvent& OnTurnEndedEvent() = 0;
};
