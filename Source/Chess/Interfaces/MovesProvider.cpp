// Fill out your copyright notice in the Description page of Project Settings.

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
