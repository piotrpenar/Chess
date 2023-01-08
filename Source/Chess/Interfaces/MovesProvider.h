

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "UObject/Interface.h"
#include "MovesProvider.generated.h"

UINTERFACE()
class UMovesProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IMovesProvider
{
	GENERATED_BODY()

public:
	virtual TArray<FMove> GetAvailableMoves();
	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition);
	virtual bool CanMoveThisTurn();
};
