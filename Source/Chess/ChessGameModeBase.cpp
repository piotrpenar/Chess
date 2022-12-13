// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChessGameModeBase.h"
#include "EColor.h"
#include "EPawnType.h"
#include "ChessPieces/UChessPawn.h"


void AChessGameModeBase::InitGameState()
{
	Board = new TArray();
	for (int i = 0; i < BoardSize; i++)
	{
		TArray<UChessPiece*> Row = new TArray();
		for (int j = 0; j < BoardSize; j++)
		{
			Row.Append(nullptr);
		}
		Board.Append(Row);
	}
	CreateChessPiece();
}

UChessPiece* AChessGameModeBase::GenerateChessPiece(const EPawnType Figure)
{
	TMap<EPawnType, UChessPiece> CharToTypeMap = {
		{EPawnType::Pawn, UChessPawn()},
		{EPawnType::Rook, UChessPawn()},
		{EPawnType::Knight, UChessPawn()},
		{EPawnType::Bishop, UChessPawn()},
		{EPawnType::King, UChessPawn()},
		{EPawnType::Queen, UChessPawn()},
	};

	UChessPiece Clone = UChessPiece();
	DuplicateObject(&CharToTypeMap[Figure], &Clone);
	return &Clone;
}

void AChessGameModeBase::CreateChessPiece()
{
	CreateFigures(Pawns, Men, EColor::White);
	CreateFigures(Pawns, Men, EColor::Black);
}

void AChessGameModeBase::GenerateChessRow(TArray<EPawnType> Figures, const EColor Color, const int TargetRow)
{
	for (int i = 0; i < BoardSize; i++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[i]);
		Clone->SetColor(Color);
		Clone->SetPosition(TargetRow, i);
		Board[TargetRow][i] = Clone;
	}
}

void AChessGameModeBase::CreateFigures(const TArray<EPawnType> Pawns, TArray<EPawnType> Men, const EColor Color)
{
	const bool bIsWhite = Color == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;

	if (!bIsWhite)
	{
		Algo::Reverse(Men);
	}

	GenerateChessRow(Men, Color, ManRow);
	GenerateChessRow(Pawns, Color, PawnRow);
};
