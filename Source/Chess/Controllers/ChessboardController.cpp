// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardController.h"

#include "ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Utils/ECheckmateStatus.h"
#include "Chess/Utils/F2DBoardArray.h"

void UChessboardController::CreateChessboardSimulation()
{
	SimulatedController = NewObject<UChessboardController>(this);
	SimulatedBoard = NewObject<UChessboard>(this);
	SimulatedController->Initialize(ChessData,SimulatedBoard,ChessGameState);
	SimulatedController->SetAsSimulation();
	SimulatedBoard->Initialize(ChessData,nullptr);
	SimulatedBoard->SetAsSimulated(Chessboard,SimulatedController);
}

bool UChessboardController::IsValidMove(const FVector2D Position, UObject* ChessPieceObject)
{
	if(!ChessData->IsValidBoardPosition(Position))
	{
		return false;
	}
	if(bIsSimulation)
	{
		return true;
	}
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	UChessPiece* SimulatedPiece = UChessPiecesFactory::CloneChessPiece(ChessPiece,this);
	const FVector2D PreviousPosition = FVector2D(SimulatedPiece->GetBoardPosition());
	SimulatedPiece->SetAsSimulated(SimulatedController);
	SimulatedBoard->SetPieceAtPosition(FVector2D(Position.X,Position.Y),SimulatedPiece);
	SimulatedPiece->SetPosition(Position.X,Position.Y);
	SimulatedBoard->SetPieceAtPosition(FVector2D(PreviousPosition.X,PreviousPosition.Y),nullptr);
	return !UChessRulesController::IsKingInCheck(SimulatedBoard,SimulatedPiece->GetColor());
	
	ECheckmateStatus Status = UChessRulesController::GetBoardStatusForColor(SimulatedBoard,SimulatedPiece->GetColor(),this);
	UE_LOG(LogTemp, Log, TEXT("Checkmate status for color %d is %d"),SimulatedPiece->GetColor(),Status)
	return Status == ECheckmateStatus::None;
}

void UChessboardController::Initialize(UChessData* NewChessData,UChessboard* NewBoard, TScriptInterface<IChessGameState> NewChessGameState)
{
	this->ChessData = NewChessData;
	this->Chessboard = NewBoard;
	this->ChessGameState = NewChessGameState;
}

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece,FVector2D Position)
{
	const FVector2D PreviousPosition = FVector2D(ChessPiece->GetBoardPosition());
	ChessPiece->MoveToPosition(Position,Chessboard->BoardToWorldTransform(Position));
	Chessboard->SetPieceAtPosition(Position,ChessPiece);
	Chessboard->SetPieceAtPosition(PreviousPosition,nullptr);
	ChessGameState->EndTurn();
}

TArray<FMove> UChessboardController::GetValidMovesFromPositions(TArray<FVector2D> Directions, UObject* ChessPieceObject)
 {
 	TArray<FMove> ValidMoves;
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
 	
 	for (const FVector2D PossibleMove  : Directions)
 	{
 		if (!IsValidMove(PossibleMove,ChessPiece))
 		{
			//UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(PossibleMove.ToString()))
 			continue;
 		}
 		UChessPiece* TargetObject = GetOtherPieceAtPosition(PossibleMove);
 		if (!TargetObject || TargetObject->GetColor() != ChessPiece->GetColor())
 		{
 			ValidMoves.Add(FMove(PossibleMove, TargetObject));
 		}
 	}
 	return ValidMoves;
}

TArray<FMove> UChessboardController::GetValidMovesFromDirections(TArray<FVector2D> Directions, UObject* ChessPieceObject)
{
 	TArray<FMove> AvailableMoves  = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
 	
	for (const FVector2D Direction : Directions)
	{
		FVector2D NextPosition = FVector2D(ChessPiece->GetBoardPosition());
		NextPosition += Direction;
		while (!IsValidMove(NextPosition,ChessPiece))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(NextPosition))
			{
				if (TargetObject->GetColor() != ChessPiece->GetColor())
				{
					//UE_LOG(LogTemp, Log, TEXT("Available Move - from %s to %s"),*FString(MovesData.Position.ToString()),*FString(CurrentTargetPosition.ToString()))
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

UChessPiece* UChessboardController::GetOtherPieceAtPosition(const FVector2D BoardPosition) const
{
	return static_cast<UChessPiece*>(Chessboard->GetPieceAtPosition(BoardPosition));
}

void UChessboardController::SetAsSimulation()
{
	bIsSimulation = true;
}
