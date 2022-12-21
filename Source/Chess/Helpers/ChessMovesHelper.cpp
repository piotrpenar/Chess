#include "ChessMovesHelper.h"

#include "Chess/Utils/ChessMovesData.h"
#include "Chess/Interfaces/ChessBoardProvider.h"

 TArray<FMove> UChessMovesHelper::GetValidMovesFromPositions(FChessMovesData& MovesData)
 {
 	TArray<FMove> ValidMoves;
 	
 	for ( FVector2D PossibleMove  : MovesData.Directions)
 	{
 		if (!(MovesData.BoardProvider->IsValidMove(PossibleMove,MovesData.ChessPiece)))
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

TArray<FMove> UChessMovesHelper::GetValidMovesFromDirections(FChessMovesData& MovesData)
{
 	TArray<FMove> AvailableMoves  = TArray<FMove>();
 	
	for (const FVector2D Direction : MovesData.Directions)
	{
		FVector2D NextPosition = FVector2D(MovesData.Position);
		NextPosition += Direction;
		while (!(MovesData.BoardProvider->IsValidMove(NextPosition,MovesData.ChessPiece)))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(MovesData,NextPosition))
			{
				if (TargetObject->GetColor() != MovesData.Color)
				{
					//UE_LOG(LogTemp, Log, TEXT("Avaliable Move - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
					AvailableMoves.Add(FMove(NextPosition, TargetObject));
					break;
				}
				//UE_LOG(LogTemp, Log, TEXT("There is friendly unit here "))
				break;
			}
			else
			{
				//UE_LOG(LogTemp, Log, TEXT("Avaliable Move - empty from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
				AvailableMoves.Add(FMove(NextPosition, TargetObject));
			}
			NextPosition += Direction;
		}
		//UE_LOG(LogTemp, Log, TEXT("Invalid Direction - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
	}
 	//UE_LOG(LogTemp, Log, TEXT("Finished Directions"))
	return AvailableMoves;
}

UChessPiece* UChessMovesHelper::GetOtherPieceAtPosition(const FChessMovesData& MovesData, const FVector2D BoardPosition) 
{
	return static_cast<UChessPiece*>(MovesData.BoardProvider->GetPieceAtPosition(BoardPosition));
}