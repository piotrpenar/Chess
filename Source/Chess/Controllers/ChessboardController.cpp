// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardController.h"

#include "ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Helpers/ChessPiecesFactory.h"

void UChessboardController::CreateChessboardSimulation()
{
	SimulatedController = NewObject<UChessboardController>(this);
	SimulatedBoard = NewObject<UChessboard>(this);
	SimulatedController->Initialize(ChessData, SimulatedBoard, ChessGameState);
	SimulatedController->SetAsSimulation();
	SimulatedBoard->Initialize(ChessData, nullptr);
	SimulatedBoard->SetAsSimulated(Chessboard, SimulatedController);
}

bool UChessboardController::IsValidMove(const FIntPoint Position, UObject* ChessPieceObject)
{
	if (!ChessData->IsValidBoardPosition(Position))
	{
		return false;
	}
	if (bIsSimulation)
	{
		return true;
	}
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	FIntPoint PreviousPosition = ChessPiece->GetBoardPosition();
	UChessPiece* SimulatedPiece = SimulatedBoard->GetPieceAtPosition(PreviousPosition);
	UChessPiece* SimulatedTargetPiece = SimulatedBoard->GetPieceAtPosition(Position);
	if (!SimulatedPiece)
	{
		UE_LOG(LogTemp, Log, TEXT("Cloud not find simulated piece in position %s"), *FString(PreviousPosition.ToString()))
		return false;
	}
	if (SimulatedTargetPiece && SimulatedTargetPiece->GetColor() == SimulatedPiece->GetColor())
	{
		return false;
	}
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, nullptr);
	bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedBoard, SimulatedPiece->GetColor());
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedTargetPiece);
	return !bIsKingInCheck;
}

void UChessboardController::Initialize(UChessData* NewChessData, UChessboard* NewBoard, TScriptInterface<IChessGameState> NewChessGameState)
{
	this->ChessData = NewChessData;
	this->Chessboard = NewBoard;
	this->ChessGameState = NewChessGameState;
}

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece, FIntPoint Position)
{
	const FIntPoint PreviousPosition = FIntPoint(ChessPiece->GetBoardPosition());
	ChessPiece->MoveToPosition(Position, Chessboard->BoardToWorldTransform(Position).GetTranslation());
	Chessboard->SetPieceAtPosition(Position, ChessPiece);
	Chessboard->SetPieceAtPosition(PreviousPosition, nullptr);
	UChessPiece* SimulatedChessPiece = SimulatedController->GetOtherPieceAtPosition(PreviousPosition);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedChessPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, nullptr);
	ChessGameState->EndTurn();
}

TArray<FMove> UChessboardController::GetValidMovesFromPositions(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> ValidMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> PossibleMoves = TArray(InputDirections);

	for (int i = 0; i < PossibleMoves.Num(); i++)
	{
		FIntPoint PossibleMove = PossibleMoves[i];
		if (!IsValidMove(PossibleMove, ChessPiece))
		{
			//FString text = FString(ChessPiece->GetBoardPosition().ToString());
			//UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"),*FString(text),*FString(PossibleMove.ToString()))
			continue;
		}
		UChessPiece* TargetObject = GetOtherPieceAtPosition(PossibleMove);
		if (!TargetObject || TargetObject->GetColor() != ChessPiece->GetColor())
		{
			ValidMoves.Add(FMove(ChessPiece, PossibleMove, TargetObject));
		}
	}
	return ValidMoves;
}

TArray<FMove> UChessboardController::GetValidMovesFromDirections(TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> AvailableMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> Directions = TArray(InputDirections);

	for (int i = 0; i < Directions.Num(); i++)
	{
		FIntPoint Direction = Directions[i];
		FIntPoint NextPosition = FIntPoint(ChessPiece->GetBoardPosition());
		NextPosition += Direction;
		while (IsValidMove(NextPosition, ChessPiece))
		{
			if (UChessPiece* TargetObject = GetOtherPieceAtPosition(NextPosition))
			{
				if (TargetObject->GetColor() != ChessPiece->GetColor())
				{
					AvailableMoves.Add(FMove(ChessPiece, NextPosition, TargetObject));
					break;
				}
				break;
			}
			else
			{
				AvailableMoves.Add(FMove(ChessPiece, NextPosition, TargetObject));
			}
			NextPosition += Direction;
		}
	}
	return AvailableMoves;
}

TArray<FMove> UChessboardController::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	EFigure TargetFigure = ChessPiece->GetFigureType();
	if (TargetFigure == EFigure::Pawn)
	{
		return GetPawnSpecialMoves(ChessPiece);
	}
	if (TargetFigure == EFigure::King)
	{
		return GetKingSpecialMoves(ChessPiece);
	}

	return {};
}

UChessPiece* UChessboardController::GetOtherPieceAtPosition(const FIntPoint BoardPosition) const
{
	return Chessboard->GetPieceAtPosition(BoardPosition);
}

void UChessboardController::SetAsSimulation()
{
	bIsSimulation = true;
}

TArray<FMove> UChessboardController::GetKingSpecialMoves(UChessPiece* KingPiece)
{
	return {};
}

bool UChessboardController::CanPawnDoubleMove(UChessPiece* ChessPiece, FIntPoint PawnPos, int Direction)
{
	TArray<FMove> SpecialMoves;
	bool canDoubleMove = true;
	FIntPoint TargetPosition = PawnPos;
	for (int i = 0; i < 2; i++)
	{
		TargetPosition += FIntPoint(0, Direction);
		UChessPiece* OtherPiece = Chessboard->GetPieceAtPosition(TargetPosition);
		if (OtherPiece)
		{
			canDoubleMove = false;
		}
	}
	if (canDoubleMove && IsValidMove(TargetPosition, ChessPiece))
	{
		return true;
	}

	return false;
}

TArray<FMove> UChessboardController::GetEnPassantMoves(UChessPiece* ChessPiece, FIntPoint PawnPos, const int Direction)
{
	TArray<FMove> SpecialMoves;
	TArray EnPassantPositions =
	{
		FIntPoint(PawnPos.X - 1, PawnPos.Y),
		FIntPoint(PawnPos.X + 1, PawnPos.Y)
	};
	for (FIntPoint Position : EnPassantPositions)
	{
		if (!ChessData->IsValidBoardPosition(Position))
		{
			continue;
		}
		UChessPiece* OtherPiece = Chessboard->GetPieceAtPosition(Position);
		if (OtherPiece && OtherPiece->GetFigureType() == EFigure::Pawn && OtherPiece->GetColor() != ChessPiece->GetColor())
		{
			UChessPawn* OtherPawn = reinterpret_cast<UChessPawn*>(OtherPiece);
			if (!OtherPawn->IsValidPassantTarget())
			{
				continue;
			}
			const FIntPoint PositionBehindTarget = Position + FIntPoint(0, Direction);
			if (IsValidMove(PositionBehindTarget, ChessPiece))
			{
				SpecialMoves.Add(FMove(ChessPiece, PositionBehindTarget, OtherPiece));
			}
		}
	}
	return SpecialMoves;
}

TArray<FMove> UChessboardController::GetPawnSpecialMoves(UChessPiece* ChessPiece)
{
	TArray<FMove> SpecialMoves;
	const FIntPoint PawnPosition = ChessPiece->GetBoardPosition();
	UChessPawn* Pawn = reinterpret_cast<UChessPawn*>(ChessPiece);
	const bool bHasMoved = Pawn->HasMoved();

	const int Direction = ChessPiece->GetColor() == EColor::White ? 1 : -1;

	if (bHasMoved)
	{
		return GetEnPassantMoves(ChessPiece, PawnPosition, Direction);
	}
	
	if (CanPawnDoubleMove(ChessPiece, PawnPosition, Direction))
	{
		return {FMove(ChessPiece, PawnPosition + FIntPoint(0, Direction * 2), nullptr)};
	}
	
	return {};
}
