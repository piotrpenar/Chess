// Fill out your copyright notice in the Description page of Project Settings.


#include "FENNotationHelper.h"

void UFENNotationHelper::Initialize(UChessboardBase* ChessboardBase)
{
	this->BoardSize = ChessboardBase->GetBoardSize();
	this->Chessboard = ChessboardBase;
}

FString UFENNotationHelper::GetCharFromFigure(const EFigure Figure)
{
	TArray<FString> Keys;
	FENCharToFigureMap.GetKeys(Keys);
	for (const auto& Key : Keys)
	{
		if (FENCharToFigureMap[Key] == Figure)
		{
			return Key;
		}
	}
	return TEXT("?");
}

EFigure UFENNotationHelper::GetFigureFromChar(const TCHAR& Char)
{
	const FString CharString = FString::Chr(Char).ToUpper();
	if (FENCharToFigureMap.Contains(CharString))
	{
		return FENCharToFigureMap[CharString];
	}
	return EFigure::Pawn;
}

EFigure UFENNotationHelper::GetFigureFromString(const FString& Char)
{
	if (FENCharToFigureMap.Contains(Char.ToUpper()))
	{
		return FENCharToFigureMap[Char];
	}
	return EFigure::Pawn;
}

FString UFENNotationHelper::GetPieceFENNotation(UChessPiece* Piece)
{
	const FString Symbol = GetCharFromFigure(Piece->GetFigureType());
	return Piece->GetColor() == EColor::White ? Symbol.ToUpper() : Symbol.ToLower();
}

FString UFENNotationHelper::GenerateFENNotation() const
{
	FString FENString(TEXT(""));
	for (int i = BoardSize - 1; i >= 0; i--)
	{
		int Empty = 0;
		for (int j = BoardSize - 1; j >= 0; j--)
		{
			UChessPiece* Piece = Chessboard->GetPieceAtPosition(FIntPoint(j, i));
			if (Piece == nullptr)
			{
				Empty++;
				continue;
			}
			if (Empty > 0)
			{
				FENString.Append(FString::FromInt(Empty));
				Empty = 0;
			}
			FENString.Append(GetPieceFENNotation(Piece));
		}
		if (Empty > 0)
		{
			FENString.Append(FString::FromInt(Empty));
		}

		if (i == 0)
		{
			continue;
		}
		FENString.Append("/");
	}
	return FENString;
}
