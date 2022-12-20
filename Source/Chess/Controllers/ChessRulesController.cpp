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
	if(CheckForMate(WhitePieces,BlackKing))
	{
		CheckForCheckMate(WhitePieces,BlackPieces,BlackKing);
	};
	CheckForMate(BlackPieces,WhiteKing);
}



TArray<UChessPiece*> UChessRulesController::CheckForMate(TArray<UChessPiece*> EnemyPieces, UChessPiece* King)
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
	if(EndangeringFigures.Num() > 0)
	{
		CheckForCheckMate()
	}
}

//TODO: Refactor This Function
bool UChessRulesController::CheckMateStatus(TArray<UChessPiece*> EnemyPieces,TArray<UChessPiece*> AllyPieces, UChessPiece* King)
{
	TArray<UChessPiece*> EndangeringFigures;
	TArray<struct {FMove Move; UChessPiece* Figure;}> AllEnemyAvailableMoves;  
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
			AllEnemyAvailableMoves.Add({Move,EnemyPiece});
		}
	}
	TArray<FMove> KingMoves = King->GetAvailableMoves();
	for(FMove KingMove : KingMoves)
	{
		if(AllEnemyAvailableMoves.FindByPredicate([&KingMove](FMove Move){return KingMove.TargetPosition == Move.TargetPosition;})==nullptr)
		{
			return false;
		}
	}
	if(EndangeringFigures.Num() > 1)
	{
		return true;
	}
	UChessPiece* EndangeringFigure = EndangeringFigures[0];
	TArray<FMove> EndangeringFigureMoves = EndangeringFigure->GetAvailableMoves();
	EFigureType EnemyFigureType = EndangeringFigure->GetFigureType();
	for (auto AllyPiece : AllyPieces)
	{
		TArray<FMove>  AllyAvailableMoves = AllyPiece->GetAvailableMoves();
		for (auto AllyMove : AllyAvailableMoves)
		{
			UChessPiece* TargetPiece = static_cast<UChessPiece*>(AllyMove.TargetObject);
			if(TargetPiece == EndangeringFigure)
			{
				//TODO: Implement those functions
				// if(IsValidMove())
				// {
				// 	return false;
				// }
			}
			if(EnemyFigureType != EFigureType::Knight)
			{
				//TODO: Verify This Function
				if(EndangeringFigureMoves.FindByPredicate([&AllyMove](FMove Move){return AllyMove.TargetPosition == Move.TargetPosition;})==nullptr)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
	}
	
	
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