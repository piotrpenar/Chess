// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void Initialize(const UChessData* ChessDataReference)
	{
		this->BoardSize = ChessDataReference->GetBoardSize();
	}

	void GenerateFENNotation(TArray<F2DBoardArray>& Board)
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
};
