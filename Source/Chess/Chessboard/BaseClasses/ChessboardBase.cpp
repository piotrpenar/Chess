// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardBase.h"

void UChessboardBase::Initialize(UChessData* ChessDataReference)
{
	ChessData = ChessDataReference;
}

void UChessboardBase::GenerateEmptyBoard()
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

UChessPiece* UChessboardBase::GetPieceAtPosition(const FIntPoint BoardPosition)
{
	if (!ChessData->IsValidBoardPosition(BoardPosition))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get object from %s"), *FString(BoardPosition.ToString()))
		return nullptr;
	}
	UObject* Object = Board[BoardPosition.X][BoardPosition.Y];
	return Cast<UChessPiece>(Object);
}

void UChessboardBase::SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece)
{
	if (!ChessData->IsValidBoardPosition(Position))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot set any object at %s"), *FString(Position.ToString()))
		return;
	}
	Board[Position.X].Set(Position.Y, ChessPiece);
	if (ChessPiece)
	{
		ChessPiece->SetPosition(Position);
	}
}

void UChessboardBase::MovePieceFromToPosition(UChessPiece* ChessPiece, const FIntPoint FromPosition, const FIntPoint ToPosition)
{
	SetPieceAtPosition(ToPosition, ChessPiece);
	Board[FromPosition.X].Set(FromPosition.Y, nullptr);
}

TArray<UChessPiece*> UChessboardBase::GetAllPiecesOfColor(const EColor Color) const
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
			UChessPiece* ChessPiece = Cast<UChessPiece>(ChessPieceObject);
			if (ChessPiece->GetColor() == Color)
			{
				Pieces.Add(ChessPiece);
			}
		}
	}
	return Pieces;
}

TArray<UChessPiece*> UChessboardBase::GetChessPieces(const EColor Color, const EFigure FigureType) const
{
	TArray<UChessPiece*> AllChessPieces = GetAllPiecesOfColor(Color);
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
