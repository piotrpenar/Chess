// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRook.h"
#include "Chess/Utils/F2dBoardArray.h"

TArray<FMove> UChessRook::GetAvailableMoves() const
{
	TArray<FVector2D> Directions = {
		FVector2D(-1, -1),
		FVector2D(-1, 1),
		FVector2D(1, -1),
		FVector2D(1, 1),
	};
	
	TArray<FMove> AvailableMoves;
	for (const FVector2D Direction : Directions)
	{
		FVector2D CurrentTargetPosition = BoardPosition;
		CurrentTargetPosition += Direction;
		while (ChessData->IsValidPosition(CurrentTargetPosition))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(CurrentTargetPosition))
			{
				if (TargetObject->GetColor() != Color)
				{
					AvailableMoves.Add(FMove(CurrentTargetPosition, TargetObject));
				}
				else
				{
					break;
				}
			}
			else
			{
				AvailableMoves.Add(FMove(CurrentTargetPosition, TargetObject));
			}
			CurrentTargetPosition += Direction;
		}
	}
	return AvailableMoves;
	
}
