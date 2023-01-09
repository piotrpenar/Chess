#include "ChessboardController.h"
#include "Chess/Controllers/ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"

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
	const FIntPoint PreviousPosition = ChessPiece->GetBoardPosition();
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
	const bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedBoard, SimulatedPiece->GetColor());
	SimulatedBoard->SetPieceAtPosition(PreviousPosition, SimulatedPiece);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedTargetPiece);
	return !bIsKingInCheck;
}

void UChessboardController::AdjustMoveType(FMove* Move) const
{
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(Move->SourcePiece);
	const bool bIsOnBoardEdge = Move->TargetPosition.Y == 0 || Move->TargetPosition.Y == ChessData->GetBoardSize() - 1;
	const bool bIsValidPawn = SourcePiece && SourcePiece->GetFigureType() == EFigure::Pawn;
	if (bIsValidPawn && bIsOnBoardEdge)
	{
		Move->MoveType = EMoveType::PawnPromotion;
	}
}

void UChessboardController::Initialize(UChessData* NewChessData, UChessboard* NewBoard, const TScriptInterface<ITurnsProvider> NewChessGameState)
{
	this->ChessData = NewChessData;
	this->Chessboard = NewBoard;
	this->ChessGameState = NewChessGameState;
}

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece, const FIntPoint Position) const
{
	const FIntPoint PreviousPosition = FIntPoint(ChessPiece->GetBoardPosition());
	ChessPiece->MoveToPosition(Position, Chessboard->BoardToWorldTransform(Position).GetTranslation());
	Chessboard->MovePieceFromToPosition(ChessPiece, PreviousPosition, Position);
	UChessPiece* SimulatedChessPiece = SimulatedController->GetPieceAtPosition(PreviousPosition);
	SimulatedBoard->MovePieceFromToPosition(SimulatedChessPiece, PreviousPosition, Position);
	ChessGameState->EndTurn();
}

void UChessboardController::RemoveChessPieceAtPosition(const FIntPoint Position) const
{
	Chessboard->SetPieceAtPosition(Position, nullptr);
	SimulatedBoard->SetPieceAtPosition(Position, nullptr);
}

TArray<FMove> UChessboardController::GetValidMovesFromPositions(const TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> ValidMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> PossibleMoves = TArray(InputDirections);

	for (int i = 0; i < PossibleMoves.Num(); i++)
	{
		const FIntPoint PossibleMove = PossibleMoves[i];
		if (!IsValidMove(PossibleMove, ChessPiece))
		{
			continue;
		}
		UChessPiece* TargetObject = GetPieceAtPosition(PossibleMove);
		if (!TargetObject || TargetObject->GetColor() != ChessPiece->GetColor())
		{
			FMove Move = FMove(ChessPiece, PossibleMove, TargetObject);
			AdjustMoveType(&Move);
			ValidMoves.Add(Move);
		}
	}
	return ValidMoves;
}

TArray<FMove> UChessboardController::GetValidMovesFromDirections(const TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> AvailableMoves = TArray<FMove>();
	UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
	TArray<FIntPoint> Directions = TArray(InputDirections);

	for (int i = 0; i < Directions.Num(); i++)
	{
		const FIntPoint Direction = Directions[i];
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
	const EFigure TargetFigure = ChessPiece->GetFigureType();
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

void UChessboardController::AddChessPieceAtPosition(UChessPiece* NewFigure, const FIntPoint Position)
{
	Chessboard->SetPieceAtPosition(Position, NewFigure);
	UChessPiece* SimulatedChessPiece = SimulatedBoard->CreateSimulatedChessPiece(SimulatedController, NewFigure);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedChessPiece);
}

TArray<FMove> UChessboardController::GetKingSpecialMoves(UChessPiece* KingPiece)
{
	TArray<FMove> SpecialMoves;
	const FIntPoint KingPos = KingPiece->GetBoardPosition();
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
		const int SignedDistance = Rook->GetBoardPosition().X - KingPiece->GetBoardPosition().X;
		const int Direction = FMath::Sign(SignedDistance);

		const FIntPoint FinalKingPosition = KingPos + FIntPoint(Direction * 2, 0);
		if (!IsValidMove(FinalKingPosition, KingPiece))
		{
			continue;
		}

		bool bCanCastle = true;
		for (int i = KingPos.X + Direction; i < FMath::Abs(SignedDistance) - 1; i += Direction)
		{
			const FIntPoint TargetPosition = FIntPoint(i, KingPos.Y);
			if (GetPieceAtPosition(TargetPosition))
			{
				bCanCastle = false;
				break;
			}
			if (!IsValidMove(TargetPosition, KingPiece))
			{
				bCanCastle = false;
				break;
			}
		}
		if (!bCanCastle)
		{
			continue;
		}

		SpecialMoves.Add(FMove(KingPiece, FinalKingPosition, Rook, EMoveType::Castling));
	}
	return SpecialMoves;
}

TArray<UChessPiece*> UChessboardController::GetChessPiecesOfType(const EColor Color, const EFigure FigureType) const
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

bool UChessboardController::CanPawnDoubleMove(UChessPiece* ChessPiece, const FIntPoint PawnPos, const int Direction)
{
	if (ChessPiece->HasMoved())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Double Move"))
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Has not moved"))
	TArray<FMove> SpecialMoves;
	bool bCanDoubleMove = true;
	FIntPoint TargetPosition = PawnPos;
	for (int i = 0; i < 2; i++)
	{
		TargetPosition += FIntPoint(0, Direction);
		if (!ChessData->IsValidBoardPosition(TargetPosition))
		{
			bCanDoubleMove = false;
			break;
		}
		const UChessPiece* OtherPiece = Chessboard->GetPieceAtPosition(TargetPosition);
		if (OtherPiece)
		{
			bCanDoubleMove = false;
			break;
		}
	}
	if (bCanDoubleMove && IsValidMove(TargetPosition, ChessPiece))
	{
		return true;
	}

	return false;
}

TArray<FMove> UChessboardController::GetEnPassantMoves(UChessPiece* ChessPiece, const FIntPoint PawnPos, const int Direction)
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
