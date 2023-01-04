// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameState.h"


// Add default functionality here for any IChessGameState functions that are not pure virtual.
EColor IChessGameState::GetCurrentPlayer()
{
	return EColor::White;
}

void IChessGameState::EndTurn()
{
}
