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