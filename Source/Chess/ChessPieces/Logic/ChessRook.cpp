// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRook.h"

#include "Chess/Helpers/ChessMovesHelper.h"

EFigureType UChessRook::GetFigureType()
{
	return EFigureType::Rook;
}

TArray<FMove> UChessRook::GetAvailableMoves()
{
	TArray<FVector2D> Directions = {
		FVector2D(1, 0),
		FVector2D(-1, 0),
		FVector2D(0, -1),
		FVector2D(0, 1),
	};
	return UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData(Directions, BoardProvider, Color, BoardPosition,this), BoardProvider.GetInterface());
}
