// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChessGameModeBase.h"
#include "EColor.h"
#include "EFigureType.h"
#include "ChessPieces/UChessPawn.h"


void AChessGameModeBase::InitializeChessPieces()
{
	FigureTypeMap = TMap<EFigureType,UChessPiece*>();
	UChessPawn Pawn = UChessPawn();
	UChessPawn Rook = UChessPawn();
	UChessPawn Knight = UChessPawn();
	UChessPawn Bishop = UChessPawn();
	UChessPawn King = UChessPawn();
	UChessPawn Queen = UChessPawn();
	FigureTypeMap.Add(EFigureType::Pawn,&Pawn);
	FigureTypeMap.Add(EFigureType::Rook,&Rook);
	FigureTypeMap.Add(EFigureType::Knight,&Knight);
	FigureTypeMap.Add(EFigureType::Bishop,&Bishop);
	FigureTypeMap.Add(EFigureType::King,&King);
	FigureTypeMap.Add(EFigureType::Queen,&Queen);
}

void AChessGameModeBase::InitGameState()
{
	InitializeChessPieces();
	for (int i = 0; i < BoardSize; i++)
	{
		TArray<UChessPiece*> Row = TArray<UChessPiece*>();
		for (int j = 0; j < BoardSize; j++)
		{
			Row.Add(nullptr);
		}
		Board.Add(F2DBoardArray());
		Board[i] = Row;
	}
	CreateChessPiece();
}

UChessPiece* AChessGameModeBase::GenerateChessPiece(const EFigureType Figure)
{
	UChessPiece Clone = UChessPiece();
	DuplicateObject(FigureTypeMap[Figure], &Clone);
	return nullptr;
}

void AChessGameModeBase::CreateChessPiece()
{
	CreateFigures(EColor::White);
	CreateFigures(EColor::Black);
}

void AChessGameModeBase::GenerateChessRow(TArray<EFigureType> Figures, const EColor Color, const int TargetRow)
{
	for (int i = 0; i < BoardSize; i++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[i]);
		Clone->SetColor(Color);
		Clone->SetPosition(TargetRow, i);
		Board[TargetRow].Set(i,Clone);
	}
}

void AChessGameModeBase::CreateFigures(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigureType> MenTargetArray = Men;

	if (!bIsWhite)
	{
		Algo::Reverse(MenTargetArray);
	}

	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(Pawns, FigureColor, PawnRow);
};
