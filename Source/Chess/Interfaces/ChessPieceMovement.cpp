#pragma once
#include "ChessPieceMovement.h"

TArray<FMove> IChessPieceMovement::GetAvailableMoves()
{
	return {};
}

void IChessPieceMovement::MoveToPosition(FIntPoint Position, FVector ActorPosition)
{
}
