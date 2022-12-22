// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRook.h"


EFigure UChessRook::GetFigureType()
{
	return EFigure::Rook;
}

TArray<FVector2D> UChessRook::GetPossibleDirections() const
{
	return  {
		FVector2D(1, 0),
		FVector2D(-1, 0),
		FVector2D(0, -1),
		FVector2D(0, 1),
	};
}

TArray<FMove> UChessRook::GetAvailableMoves()
{
	return MovementVerifier->GetValidMovesFromDirections(GetPossibleDirections(),this);
}