// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Chessboard.h"

#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Utils/F2DBoardArray.h"


void UChessboard::Initialize(UChessData* NewChessData, AActor* NewChessBoardOrigin) 
{
	this->ChessData = NewChessData;
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
	const FIntPoint Position = FIntPoint(X,Y);
	return BoardToWorldTransform(Position);
}

FTransform UChessboard::BoardToWorldTransform(const FIntPoint Position) const
{
	FTransform Transform= GetChessBoardTransform();
	const float BoardDistance = ChessData->GetBoardCheckerSize();
	FVector PositionOffset = FVector(BoardDistance/2 + Position.X*BoardDistance,BoardDistance/2 + Position.Y*BoardDistance,ChessData->GetBoardOffset());
	PositionOffset = Transform.Rotator().RotateVector(PositionOffset);
	Transform.SetLocation(Transform.GetLocation() + PositionOffset);
	return Transform;
}

UChessPiece* UChessboard::GetPieceAtPosition(FIntPoint BoardPosition)
{
	UObject* Object = Board[BoardPosition.X][BoardPosition.Y];
	//UE_LOG(LogTemp, Log, TEXT("Getting object from %s"),*FString(BoardPosition.ToString()))
	return static_cast<UChessPiece*>(Object);
}

void UChessboard::SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece)
{
	UObject* CurrentObject = Board[Position.X][Position.Y];
	if(CurrentObject)
	{
		if(ChessPiece)
		{
			static_cast<UChessPiece*>(CurrentObject)->DestroyChessPiece();
		}
	}
	//UE_LOG(LogTemp, Log, TEXT("Setting object at %s"),*FString(Vector2.ToString()))
	Board[Position.X].Set(Position.Y,ChessPiece);
	if(ChessPiece)
	{
		ChessPiece->SetPosition(Position);
	}
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


UChessPiece* UChessboard::GetChessPiece(const EFigure Figure,const EColor Color)
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

void UChessboard::SetAsSimulated(UChessboard* OriginalBoard,TScriptInterface<IMovementVerifier> SimulatedMovementVerifier)
{
	bIsSimulation=true;
	for (int i=0;i<ChessData->GetBoardSize();i++)
	{
		F2DBoardArray NewRow = F2DBoardArray();
		for (int j=0;j<ChessData->GetBoardSize();j++)
		{
			UChessPiece* ChessPiece = OriginalBoard->GetPieceAtPosition(FIntPoint(i,j));
			if (!ChessPiece)
			{
				NewRow.Add(nullptr);
				continue;
			}
			UChessPiece* Clone = UChessPiecesFactory::CloneChessPiece(ChessPiece,this);
			Clone->SetAsSimulated(SimulatedMovementVerifier);
			NewRow.Add(Clone);
		}
		Board.Add(NewRow);
	}
}
