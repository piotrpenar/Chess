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
		UE_LOG(LogTemp, Log, TEXT("Invalid board position"))
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
		UE_LOG(LogTemp, Log, TEXT("Same color %s"), *FString(Position.ToString()))
		return false;
	}
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, nullptr);
	bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedBoard, SimulatedPiece->GetColor());
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedTargetPiece);
	return !bIsKingInCheck;
}

void UChessboardController::AdjustMoveType(FMove* Move)
{
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(Move->SourcePiece);
	bool bIsOnBoardEdge = Move->TargetPosition.Y == 0 || Move->TargetPosition.Y == ChessData->GetBoardSize() - 1;
	bool bIsValidPawn = SourcePiece && SourcePiece->GetFigureType() == EFigure::Pawn;
	if (bIsValidPawn && bIsOnBoardEdge)
	{
		Move->MoveType = EMoveType::PawnPromotion;
	}
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
	Chessboard->MovePieceFromToPosition(ChessPiece, PreviousPosition, Position);
	UChessPiece* SimulatedChessPiece = SimulatedController->GetPieceAtPosition(PreviousPosition);
	SimulatedBoard->MovePieceFromToPosition(SimulatedChessPiece, PreviousPosition, Position);
	ChessGameState->EndTurn();
}

void UChessboardController::SetChessPieceAtPosition(FIntPoint Position, UChessPiece* ChessPiece)
{
	Chessboard->SetPieceAtPosition(Position, ChessPiece);
	SimulatedBoard->SetPieceAtPosition(Position, ChessPiece);
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
			FString text = FString(ChessPiece->GetBoardPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Invalid Position - from %s to %s"),*FString(text),*FString(PossibleMove.ToString()))
			continue;
		}
		UChessPiece* TargetObject = GetPieceAtPosition(PossibleMove);
		if (!TargetObject || TargetObject->GetColor() != ChessPiece->GetColor())
		{
			FString text = FString(ChessPiece->GetBoardPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("VALID Position - from %s to %s"),*FString(text),*FString(PossibleMove.ToString()))
			FMove Move = FMove(ChessPiece, PossibleMove, TargetObject);
			AdjustMoveType(&Move);
			ValidMoves.Add(Move);
		}
		else if(TargetObject->GetColor() == ChessPiece->GetColor())
		{
			FString text = FString(ChessPiece->GetBoardPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Same colors - from %s to %s"),*FString(text),*FString(PossibleMove.ToString()))
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
			if (UChessPiece* TargetObject = GetPieceAtPosition(NextPosition))
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

UChessPiece* UChessboardController::GetPieceAtPosition(const FIntPoint BoardPosition) const
{
	return Chessboard->GetPieceAtPosition(BoardPosition);
}

void UChessboardController::SetAsSimulation()
{
	bIsSimulation = true;
}

TArray<FMove> UChessboardController::GetKingSpecialMoves(UChessPiece* KingPiece)
{
	TArray<FMove> SpecialMoves;
	FIntPoint KingPos = KingPiece->GetBoardPosition();
	if (KingPiece->HasMoved())
	{
		return SpecialMoves;
	}
	TArray<UChessPiece*> Rooks = GetChessPiecesOfType(KingPiece->GetColor(), EFigure::Rook);
	for (UChessPiece* Rook : Rooks)
	{
		if (Rook->HasMoved() || Rook->GetBoardPosition().Y != KingPos.Y)
		{
			continue;
		}
		int SignedDistance =  Rook->GetBoardPosition().X - KingPiece->GetBoardPosition().X;
		int Direction = FMath::Sign(SignedDistance);

		FIntPoint FinalKingPosition = KingPos + FIntPoint(Direction*2,0);
		if(!IsValidMove( FinalKingPosition,KingPiece))
		{
			continue;
		}
		
		bool bCanCastle = true;
		for (int i = KingPos.X+Direction; i < FMath::Abs(SignedDistance)-1; i += Direction)
		{
			FIntPoint TargetPosition = FIntPoint(i,KingPos.Y);
			if(GetPieceAtPosition(TargetPosition))
			{
				bCanCastle = false;
				break;
			}
			if(!IsValidMove(TargetPosition,KingPiece))
			{
				bCanCastle = false;
				break;
			}
		}
		if(!bCanCastle)
		{
			continue;
		}

		SpecialMoves.Add(FMove(KingPiece,FinalKingPosition,Rook,EMoveType::Castling));
	}
	return SpecialMoves;
}

TArray<UChessPiece*> UChessboardController::GetChessPiecesOfType(EColor Color, EFigure FigureType)
{
	TArray<UChessPiece*> AllChessPieces = Chessboard->GetAllPiecesOfColor(Color);
	TArray<UChessPiece*> FiguresOfType;
	for (UChessPiece* Piece : AllChessPieces)
	{
		if (Piece->GetFigureType() == FigureType)
		{
			FiguresOfType.Add(Piece);
		}
	}
	return FiguresOfType;
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
				SpecialMoves.Add(FMove(ChessPiece, PositionBehindTarget, OtherPiece, EMoveType::EnPassant));
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
		return {FMove(ChessPiece, PawnPosition + FIntPoint(0, Direction * 2), nullptr, EMoveType::DoubleMove)};
	}

	return {};
}
