#pragma once
#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "ChessPieceMovement.generated.h"

UINTERFACE()
class UChessPieceMovement : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IChessPieceMovement
{
	GENERATED_BODY()

public:
	virtual TArray<FMove> GetAvailableMoves();
	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition);
};
