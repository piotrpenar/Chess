// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementVerifier.h"
#include "Chess/Utils/FMove.h"


// Add default functionality here for any IIMovementVeryfier functions that are not pure virtual.

bool IMovementVerifier::IsValidMove(const FIntPoint Position, UObject* ChessPiece)
{
	return false;
}

TArray<FMove> IMovementVerifier::GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementVerifier::GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementVerifier::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	return {};
}
