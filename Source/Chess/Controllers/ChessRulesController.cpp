// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRulesController.h"

#include "Chess/ChessPieces/ChessPiece.h"

TArray<UChessPiece*> UChessRulesController::GetAllPiecesOfColor(TArray<F2DBoardArray>* Board, EColor Color)
{
	TArray<UChessPiece*> Pieces;
	for (auto Row : *(Board))
	{
		for (auto ChessPiece : Row.Array)
		{
			if(!ChessPiece)
			{
				continue;
			}
			UChessPiece* Piece = static_cast<UChessPiece*>(ChessPiece);
			if(Piece->GetColor() == Color)
			{
				Pieces.Add(Piece);
			}
		}
	}
	return Pieces;
}

UChessPiece* UChessRulesController::GetFigureFromArray(TArray<UChessPiece*> Array, EFigureType Figure)
{
	for (auto ChessPiece : Array)
	{
		if(ChessPiece->GetFigureType() == Figure)
		{
			return ChessPiece;
		}
	}
	return nullptr;
}

void UChessRulesController::CheckBoardStatus(TArray<F2DBoardArray>* Board)
{
	TArray<UChessPiece*> WhitePieces = GetAllPiecesOfColor(Board,EColor::White); 
	TArray<UChessPiece*> BlackPieces = GetAllPiecesOfColor(Board,EColor::Black); 
	UChessPiece* WhiteKing = GetFigureFromArray(WhitePieces,EFigureType::King);
	UChessPiece* BlackKing = GetFigureFromArray(WhitePieces,EFigureType::King);
	CheckForMate(WhitePieces,BlackKing);
	CheckForMate(BlackPieces,WhiteKing);
}



void UChessRulesController::CheckForMate(TArray<UChessPiece*> EnemyPieces, UChessPiece* King)
{
	TArray<UChessPiece*> EndangeringFigures;
	for (auto EnemyPiece : EnemyPieces)
	{
		TArray<FMove> EnemyAvailableMoves = EnemyPiece->GetAvailableMoves();
		for (auto Move : EnemyAvailableMoves)
		{
			UChessPiece* TargetPiece = static_cast<UChessPiece*>(Move.TargetObject);
			if(TargetPiece == King)
			{
				UE_LOG(LogTemp,Log,TEXT("Mate!"))
				EndangeringFigures.Add(EnemyPiece);
			}
		}
	}
}

void UChessRulesController::CheckForCheckMate()
{
	
}

UChessPiece* UChessRulesController::FindChessPiece(TArray<F2DBoardArray>* Board,EFigureType Figure,EColor Color)
{
	for (auto Row : *(Board))
	{
		for (auto ChessPiece : Row.Array)
		{
			if(!ChessPiece)
			{
				continue;
			}
			UChessPiece* Piece = static_cast<UChessPiece*>(ChessPiece);
			if(Piece->GetFigureType() == Figure && Piece->GetColor() == Color)
			{
				return Piece;
			}
		}
	}
	return nullptr;
}