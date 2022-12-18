﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRook.h"

#include "Chess/Helpers/ChessMovesHelper.h"

TArray<FMove> UChessRook::GetAvailableMoves()
{
	TArray<FVector2D> Directions = {
		FVector2D(1, 0),
		FVector2D(-1, 0),
		FVector2D(0, -1),
		FVector2D(0, 1),
	};
	UE_LOG(LogTemp, Log, TEXT("Rook"))
	return UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData(Directions, BoardProvider, Color, BoardPosition),
	                                                      ChessData);
}