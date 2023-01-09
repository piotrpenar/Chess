#include "Chessboard.h"
#include "Chess/Helpers/ChessPiecesFactory.h"

void UChessboard::Initialize(UChessData* Data, AActor* NewChessBoardOrigin)
{
	this->ChessData = Data;
	this->ChessBoardOrigin = NewChessBoardOrigin;
};

void UChessboard::GenerateEmptyBoard()
{
	for (int i = 0; i < ChessData->GetBoardSize(); i++)
	{
		F2DBoardArray Row = F2DBoardArray();
		for (int j = 0; j < ChessData->GetBoardSize(); j++)
		{
			Row.Add(nullptr);
		}
		Board.Add(Row);
	}
}

FTransform UChessboard::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}

FTransform UChessboard::BoardToWorldTransform(const int X, const int Y) const
{
	const FIntPoint Position = FIntPoint(X, Y);
	return BoardToWorldTransform(Position);
}

FTransform UChessboard::BoardToWorldTransform(const FIntPoint Position) const
{
	FTransform Transform = GetChessBoardTransform();
	const float BoardDistance = ChessData->GetBoardCheckerSize();
	FVector PositionOffset = FVector(BoardDistance / 2 + Position.X * BoardDistance, BoardDistance / 2 + Position.Y * BoardDistance, ChessData->GetBoardOffset());
	PositionOffset = Transform.Rotator().RotateVector(PositionOffset);
	Transform.SetLocation(Transform.GetLocation() + PositionOffset);
	return Transform;
}

UChessPiece* UChessboard::GetPieceAtPosition(const FIntPoint BoardPosition)
{
	if (!ChessData->IsValidBoardPosition(BoardPosition))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get object from %s"), *FString(BoardPosition.ToString()))
		return nullptr;
	}
	UObject* Object = Board[BoardPosition.X][BoardPosition.Y];
	return static_cast<UChessPiece*>(Object);
}

void UChessboard::SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece)
{
	if (!ChessData->IsValidBoardPosition(Position))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot set any object at %s"), *FString(Position.ToString()))
		return;
	}

	const UChessPiece* CurrentObject = GetPieceAtPosition(Position);
	if (CurrentObject && !bIsSimulation)
	{
		CurrentObject->DestroyChessPiece();
	}
	Board[Position.X].Set(Position.Y, ChessPiece);
	if (ChessPiece)
	{
		ChessPiece->SetPosition(Position);
	}
}

void UChessboard::MovePieceFromToPosition(UChessPiece* ChessPiece, const FIntPoint FromPosition, const FIntPoint ToPosition)
{
	SetPieceAtPosition(ToPosition, ChessPiece);
	Board[FromPosition.X].Set(FromPosition.Y, nullptr);
}

TArray<UChessPiece*> UChessboard::GetAllPiecesOfColor(const EColor Color)
{
	TArray<UChessPiece*> Pieces;
	for (F2DBoardArray Row : Board)
	{
		for (UObject* ChessPieceObject : Row.Array)
		{
			if (!ChessPieceObject)
			{
				continue;
			}
			UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
			if (ChessPiece->GetColor() == Color)
			{
				Pieces.Add(ChessPiece);
			}
		}
	}
	return Pieces;
}


UChessPiece* UChessboard::GetChessPiece(const EFigure Figure, const EColor Color)
{
	for (F2DBoardArray Row : Board)
	{
		for (UObject* ChessPieceObject : Row.Array)
		{
			if (!ChessPieceObject)
			{
				continue;
			}
			UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
			if (ChessPiece->GetFigureType() == Figure && ChessPiece->GetColor() == Color)
			{
				return ChessPiece;
			}
		}
	}
	return nullptr;
}

UChessPiece* UChessboard::CreateSimulatedChessPiece(const TScriptInterface<IChessMovesProvider> SimulatedMovementVerifier, UChessPiece* ChessPiece)
{
	UChessPiece* Clone = UChessPiecesFactory::CloneChessPiece(ChessPiece, this);
	Clone->SetAsSimulated(SimulatedMovementVerifier);
	return Clone;
}

void UChessboard::SetAsSimulated(UChessboard* OriginalBoard, const TScriptInterface<IChessMovesProvider> SimulatedMovementVerifier)
{
	bIsSimulation = true;
	for (int i = 0; i < ChessData->GetBoardSize(); i++)
	{
		F2DBoardArray NewRow = F2DBoardArray();
		for (int j = 0; j < ChessData->GetBoardSize(); j++)
		{
			UChessPiece* ChessPiece = OriginalBoard->GetPieceAtPosition(FIntPoint(i, j));
			if (!ChessPiece)
			{
				NewRow.Add(nullptr);
				continue;
			}
			UChessPiece* Clone = CreateSimulatedChessPiece(SimulatedMovementVerifier, ChessPiece);
			NewRow.Add(Clone);
		}
		Board.Add(NewRow);
	}
}
