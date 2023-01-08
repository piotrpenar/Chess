

#pragma once

#include "MovesProvider.h"

TArray<FMove> IMovesProvider::GetAvailableMoves()
{
	return {};
}

void IMovesProvider::MoveToPosition(FIntPoint Position, FVector ActorPosition)
{
}

bool IMovesProvider::CanMoveThisTurn()
{
	return false;
}
