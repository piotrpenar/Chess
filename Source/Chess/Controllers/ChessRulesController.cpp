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

ECheckMateStatus UChessRulesController::GetBoardStatus(TArray<F2DBoardArray>* Board,IChessBoardProvider* ChessBoardProvider)
{
	TArray<UChessPiece*> WhitePieces = GetAllPiecesOfColor(Board,EColor::White); 
	TArray<UChessPiece*> BlackPieces = GetAllPiecesOfColor(Board,EColor::Black); 
	UChessPiece* WhiteKing = GetFigureFromArray(WhitePieces,EFigureType::King);
	UChessPiece* BlackKing = GetFigureFromArray(WhitePieces,EFigureType::King);
	ECheckMateStatus BlackMate = CheckForCheckMate(WhitePieces,BlackPieces,BlackKing,ChessBoardProvider);
	ECheckMateStatus WhiteMate = CheckForCheckMate(BlackPieces,WhitePieces,WhiteKing,ChessBoardProvider);
	if(BlackMate!= ECheckMateStatus::None)
	{
		UE_LOG(LogTemp,Log,TEXT("Black Mate!- %d!"),BlackMate)
	}
	if(WhiteMate!= ECheckMateStatus::None)
	{
		UE_LOG(LogTemp,Log,TEXT("White Mate - %d!"),WhiteMate)
	}
	
	
}
struct Temp{FMove Move; UChessPiece* Figure;};
//TODO: Refactor This Function
ECheckMateStatus UChessRulesController::CheckForCheckMate(TArray<UChessPiece*> EnemyPieces,TArray<UChessPiece*> AllyPieces, UChessPiece* King,IChessBoardProvider* ChessBoardProvider)
{
	ECheckMateStatus CheckResult = ECheckMateStatus::None;
	TArray<UChessPiece*> EndangeringFigures;
	TArray<Temp> AllEnemyAvailableMoves;  
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
				CheckResult = ECheckMateStatus::Mate;
			}
			AllEnemyAvailableMoves.Add({Move,EnemyPiece});
		}
	}
	
	TArray<FMove> KingMoves = King->GetAvailableMoves();
	for(FMove KingMove : KingMoves)
	{
		if(AllEnemyAvailableMoves.FindByPredicate([&KingMove](FMove Move){return KingMove.TargetPosition == Move.TargetPosition;})==nullptr)
		{
			return CheckResult;
		}
	}
	
	if(EndangeringFigures.Num() > 1)
	{
		CheckResult = ECheckMateStatus::Checkmate;
		return CheckResult;
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
				if(ChessBoardProvider->IsValidMove(AllyMove.TargetPosition,TargetPiece))
				{
					return CheckResult;
				}
			}
			if(EnemyFigureType != EFigureType::Knight)
			{
				if(EndangeringFigureMoves.FindByPredicate([&AllyMove](FMove Move){return AllyMove.TargetPosition == Move.TargetPosition;})==nullptr)
				{
					continue;
				}
				
				if(ChessBoardProvider->IsValidMove(AllyMove.TargetPosition,AllyPiece))
				{
					return CheckResult;
				}
				
			}
		}
	}
	return ECheckMateStatus::Checkmate;
}

UChessPiece* UChessRulesController::FindChessPiece(TArray<F2DBoardArray>* Board,EFigureType Figure,EColor Color)
{
	for (auto Row : *(Board))
	{
		for (const auto ChessPiece : Row.Array)
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