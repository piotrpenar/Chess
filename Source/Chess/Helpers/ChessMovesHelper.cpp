#include "ChessMovesHelper.h"

#include "Chess/Utils/ChessMovesData.h"

 TArray<FMove> UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData MovesData, const UChessData* ChessData)
 {
 	TArray<FMove> ValidMoves;

 	for ( FVector2D PossibleMove  : MovesData.Directions)
 	{
 		if (!(ChessData->IsValidPosition(PossibleMove)))
 		{
 			continue;
 		}
 		UChessPiece* TargetObject = GetOtherPieceAtPosition(MovesData,PossibleMove);
 		if (!TargetObject || TargetObject->GetColor() != MovesData.Color)
 		{
 			ValidMoves.Add(FMove(PossibleMove, TargetObject));
 		}
 	}
 	return ValidMoves;
}

TArray<FMove> UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData MovesData, UChessData* ChessData)
{
	TArray<FMove> AvailableMoves  = TArray<FMove>();
	for (const FVector2D Direction : MovesData.Directions)
	{
		FVector2D CurrentTargetPosition = MovesData.Position;
		CurrentTargetPosition += Direction;
		while (ChessData->IsValidPosition(CurrentTargetPosition))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(MovesData,CurrentTargetPosition))
			{
				if (TargetObject->GetColor() != MovesData.Color)
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

UChessPiece* UChessMovesHelper::GetOtherPieceAtPosition(FChessMovesData MovesData, FVector2D BoardPosition) 
{
	return static_cast<UChessPiece*>(MovesData.Board[BoardPosition.X][BoardPosition.Y]);
}