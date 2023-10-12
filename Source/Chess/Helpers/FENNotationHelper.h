// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/BaseClasses/ChessboardBase.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/2DBoardArray.h"
#include "UObject/Object.h"
#include "FENNotationHelper.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UFENNotationHelper : public UObject
{
	GENERATED_BODY()

	int BoardSize = 8;

	UPROPERTY()
	UChessboardBase* Chessboard;
	
	void Initialize(UChessboardBase* ChessboardBase)
	{
		this->BoardSize = ChessboardBase->GetBoardSize();
		this->Chessboard = ChessboardBase;
	}

	static FString GetPieceFENNotation(UChessPiece* Piece)
	{
		FString Symbol(TEXT(""));
		switch (Piece->GetFigureType())
		{
		case EFigure::Pawn:
			Symbol = TEXT("P");
		case EFigure::Rook:
			Symbol = TEXT("R");
		case EFigure::Knight:
			Symbol = TEXT("N");
		case EFigure::Bishop:
			Symbol = TEXT("B");
		case EFigure::Queen:
			Symbol = TEXT("Q");
		case EFigure::King:
			Symbol = TEXT("K");
		case EFigure::Invalid:
			break;
		default: ;
		}
		return Piece->GetColor() == EColor::White ? Symbol.ToUpper() : Symbol.ToLower();
	}

	void GenerateFENNotation()
	{
		FString string(TEXT(""));
		for (int i = 0; i < BoardSize; i++)
		{
			int empty = 0;
			for (int j = 0; j < BoardSize; j++)
			{
				UChessPiece* piece = Chessboard->GetPieceAtPosition(FIntPoint(i, j));
				if(piece == nullptr)
				{
					empty++;
				}
				else
				{
					if(empty > 0 )
					{
						string.Append(FString::FromInt(empty));
					}
					string.Append(GetPieceFENNotation(piece));
				}
			}
			if(empty > 0 )
			{
				string.Append(FString::FromInt(empty));
			}
			string.Append("/");
		}
	}
};
