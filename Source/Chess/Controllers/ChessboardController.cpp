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

bool UChessboardController::IsValidMove(const FIntPoint Position, UObject* ChessPieceObject)
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
	FIntPoint PreviousPosition = ChessPiece->GetBoardPosition();
	UChessPiece* SimulatedPiece = SimulatedBoard->GetPieceAtPosition(PreviousPosition);
	if(!SimulatedPiece)
	{
		return false;
	}
	SimulatedBoard->SetPieceAtPosition(FIntPoint(Position.X,Position.Y),SimulatedPiece);
	SimulatedPiece->SetPosition(Position.X,Position.Y);
	SimulatedBoard->SetPieceAtPosition(FIntPoint(PreviousPosition.X,PreviousPosition.Y),nullptr);
	bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedBoard,SimulatedPiece->GetColor());
	SimulatedBoard->SetPieceAtPosition(FIntPoint(PreviousPosition.X,PreviousPosition.Y),SimulatedPiece);
	SimulatedPiece->SetPosition(PreviousPosition.X,PreviousPosition.Y);
	SimulatedBoard->SetPieceAtPosition(FIntPoint(Position.X,Position.Y),nullptr);
	return !bIsKingInCheck;
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

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece,FIntPoint Position)
{
	const FIntPoint PreviousPosition = FIntPoint(ChessPiece->GetBoardPosition());
	ChessPiece->MoveToPosition(Position,Chessboard->BoardToWorldTransform(Position).GetTranslation());
	Chessboard->SetPieceAtPosition(Position,ChessPiece);
	Chessboard->SetPieceAtPosition(PreviousPosition,nullptr);
	UChessPiece* SimulatedChessPiece = SimulatedController->GetOtherPieceAtPosition(PreviousPosition);
	SimulatedChessPiece->SetPosition(Position);
	SimulatedBoard->SetPieceAtPosition(Position,SimulatedChessPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition,nullptr);
	ChessGameState->EndTurn();
}

TArray<FMove> UChessboardController::GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPieceObject)
 {
 	TArray<FMove> ValidMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
 	
 	for (const FIntPoint PossibleMove  : Directions)
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

TArray<FMove> UChessboardController::GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPieceObject)
{
 	TArray<FMove> AvailableMoves  = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
 	
	for (const FIntPoint Direction : Directions)
	{
		FIntPoint NextPosition = FIntPoint(ChessPiece->GetBoardPosition());
		NextPosition += Direction;
		while (IsValidMove(NextPosition,ChessPiece))
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

UChessPiece* UChessboardController::GetOtherPieceAtPosition(const FIntPoint BoardPosition) const
{
	return Chessboard->GetPieceAtPosition(BoardPosition);
}

void UChessboardController::SetAsSimulation()
{
	bIsSimulation = true;
}
