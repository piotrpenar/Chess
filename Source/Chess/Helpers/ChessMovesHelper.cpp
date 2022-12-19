#include "ChessMovesHelper.h"

#include "Chess/Utils/ChessMovesData.h"
#include "Chess/Interfaces/ChessBoardProvider.h"

 TArray<FMove> UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData MovesData, const UChessData* ChessData)
 {
 	TArray<FMove> ValidMoves;
 	
 	for ( FVector2D PossibleMove  : MovesData.Directions)
 	{
 		if (!(ChessData->IsValidPosition(PossibleMove)))
 		{
			//UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(PossibleMove.ToString()))
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
		FVector2D CurrentTargetPosition = FVector2D(MovesData.Position);
		CurrentTargetPosition += Direction;
		while (ChessData->IsValidPosition(CurrentTargetPosition))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(MovesData,CurrentTargetPosition))
			{
				if (TargetObject->GetColor() != MovesData.Color)
				{
					//UE_LOG(LogTemp, Log, TEXT("Avaliable Move - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
					AvailableMoves.Add(FMove(CurrentTargetPosition, TargetObject));
					break;
				}
				//UE_LOG(LogTemp, Log, TEXT("There is friendly unit here "))
				break;
			}
			else
			{
				//UE_LOG(LogTemp, Log, TEXT("Avaliable Move - empty from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
				AvailableMoves.Add(FMove(CurrentTargetPosition, TargetObject));
			}
			CurrentTargetPosition += Direction;
		}
		//UE_LOG(LogTemp, Log, TEXT("Invalid Direction - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
	}
 	//UE_LOG(LogTemp, Log, TEXT("Finished Directions"))
	return AvailableMoves;
}

UChessPiece* UChessMovesHelper::GetOtherPieceAtPosition(FChessMovesData MovesData, FVector2D BoardPosition) 
{
	return static_cast<UChessPiece*>(MovesData.BoardProvider->GetPieceAtPosition(BoardPosition));
}