// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiecesFactory.h"

#include "Chess/ChessPieces/Logic/ChessBishop.h"
#include "Chess/ChessPieces/Logic/ChessKing.h"
#include "Chess/ChessPieces/Logic/ChessKnight.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "Chess/ChessPieces/Logic/ChessQueen.h"
#include "Chess/ChessPieces/Logic/ChessRook.h"


UChessPiece* UChessPiecesFactory::GenerateChessPiece(const EFigureType FigureType, UObject* Initializer) 
{
	
	switch (FigureType)
	{
	case EFigureType::Pawn: 
		return NewObject<UChessPawn>(Initializer);
	case EFigureType::Rook:
		return NewObject<UChessRook>(Initializer);
	case EFigureType::Knight:
		return NewObject<UChessKnight>(Initializer);
	case EFigureType::Bishop:
		return NewObject<UChessBishop>(Initializer);
	case EFigureType::Queen:
		return NewObject<UChessQueen>(Initializer);
	case EFigureType::King:
		return NewObject<UChessKing>(Initializer);
	default:
		UE_LOG(LogTemp, Error, TEXT("Initializing piece with default type!"))
		return NewObject<UChessPiece>(Initializer);
	}
}

UChessPiece* UChessPiecesFactory::CloneChessPiece(UChessPiece* Original, UObject* Initializer)
{
	switch (Original->GetFigureType())
	{
	case EFigureType::Pawn:
		const UChessPawn* OriginalPawn = static_cast<UChessPawn*>(Original);
		return DuplicateObject(OriginalPawn,Initializer);
	case EFigureType::Rook:
		const UChessRook* OriginalRook = static_cast<UChessRook*>(Original);
		return DuplicateObject(OriginalRook,Initializer);
	case EFigureType::Knight:
		const UChessKnight* OriginalKnight = static_cast<UChessKnight*>(Original);
		return DuplicateObject(OriginalKnight,Initializer);
	case EFigureType::Bishop:
		const UChessBishop* OriginalBishop = static_cast<UChessBishop*>(Original);
		return DuplicateObject(OriginalBishop,Initializer);
	case EFigureType::Queen:
		const UChessQueen* OriginalQueen = static_cast<UChessQueen*>(Original);
		return DuplicateObject(OriginalQueen,Initializer);
	case EFigureType::King:
		const UChessKing* OriginalKing = static_cast<UChessKing*>(Original);
		return DuplicateObject(OriginalKing,Initializer);
	default:
		UE_LOG(LogTemp, Error, TEXT("Initializing piece with default type!"))
		return NewObject<UChessPiece>(Initializer);
	}
}
