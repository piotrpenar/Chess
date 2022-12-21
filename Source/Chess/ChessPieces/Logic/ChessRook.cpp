// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRook.h"

#include "Chess/Helpers/ChessMovesHelper.h"

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

FChessMovesData UChessRook::GenerateMovesData()
{
	return FChessMovesData(GetPossibleDirections(), BoardProvider, Color, BoardPosition,this);
}

TArray<FMove> UChessRook::GetAvailableMoves()
{
	const FChessMovesData PossibleMovesData = GenerateMovesData();
	return UChessMovesHelper::GetValidMovesFromDirections(PossibleMovesData);
}