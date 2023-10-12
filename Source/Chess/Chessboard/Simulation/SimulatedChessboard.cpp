// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulatedChessboard.h"

#include "Chess/Chessboard/BaseClasses/ChessboardMovementRulesBase.h"
#include "Chess/Helpers/ChessPiecesFactory.h"

UChessPiece* USimulatedChessboard::CreateSimulatedChessPiece(UChessPiece* ChessPiece)
{
	UChessPiece* Clone = UChessPiecesFactory::CloneChessPiece(ChessPiece, this);
	Clone->Initialize(ChessboardMovementRules, nullptr);
	return Clone;
}

void USimulatedChessboard::InitializeSimulatedBoard(UChessboardBase* OriginalBoard)
{
	Initialize(OriginalBoard->GetBoardSize());
	GenerateEmptyBoard();
	UChessboardMovementRulesBase* MovementRules = NewObject<UChessboardMovementRulesBase>();
	MovementRules->InitializeMovementRules(this);
	ChessboardMovementRules = MovementRules;

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			UChessPiece* ChessPiece = OriginalBoard->GetPieceAtPosition(FIntPoint(i, j));
			if (!ChessPiece)
			{
				continue;
			}
			UChessPiece* Clone = CreateSimulatedChessPiece(ChessPiece);
			Board[i].Set(j, Clone);
		}
	}
}
