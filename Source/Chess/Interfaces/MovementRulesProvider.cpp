﻿#include "MovementRulesProvider.h"
#include "Chess/Utils/FMove.h"

bool IMovementRulesProvider::IsValidMove(const FIntPoint Position, UObject* ChessPiece)
{
	return false;
}

TArray<FMove> IMovementRulesProvider::GetValidMovesFromPositions(const TArray<FIntPoint>& Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementRulesProvider::GetValidMovesFromDirections(const TArray<FIntPoint>& Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementRulesProvider::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	return {};
}
