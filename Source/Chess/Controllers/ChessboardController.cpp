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
	UChessPiece* SimulatedTargetPiece = SimulatedBoard->GetPieceAtPosition(Position);
	if(!SimulatedPiece)
	{
		UE_LOG(LogTemp, Log, TEXT("Cloud not find simulated piece in position %s"),*FString(PreviousPosition.ToString()))
		return false;
	}
	if(SimulatedTargetPiece && SimulatedTargetPiece->GetColor() == SimulatedPiece->GetColor())
	{
		return false;
	}
	SimulatedBoard->SetPieceAtPosition(Position,SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition,nullptr);
	bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedBoard,SimulatedPiece->GetColor());
	SimulatedBoard->SetPieceAtPosition(PreviousPosition,SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(Position,SimulatedTargetPiece);
	return !bIsKingInCheck;
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
	SimulatedBoard->SetPieceAtPosition(Position,SimulatedChessPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition,nullptr);
	ChessGameState->EndTurn();
}

TArray<FMove> UChessboardController::GetValidMovesFromPositions(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
 {
 	TArray<FMove> ValidMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> PossibleMoves = TArray(InputDirections);
 	
	for (int i = 0;i<PossibleMoves.Num();i++)
	{
		FIntPoint PossibleMove = PossibleMoves[i];
 		if (!IsValidMove(PossibleMove,ChessPiece))
 		{
 			//FString text = FString(ChessPiece->GetBoardPosition().ToString());
			//UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"),*FString(text),*FString(PossibleMove.ToString()))
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

TArray<FMove> UChessboardController::GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
 	TArray<FMove> AvailableMoves  = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> Directions = TArray(InputDirections);
 	
	for (int i = 0;i<Directions.Num();i++)
	{
		FIntPoint Direction = Directions[i];
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
 		//FString text = FString(ChessPiece->GetBoardPosition().ToString());
		//UE_LOG(LogTemp, Log, TEXT("Invalid Direction - from %s to %s"),*FString(text),*FString(NextPosition.ToString()))
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
