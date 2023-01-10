#include "ChessPiecesFactory.h"
#include "Chess/ChessPieces/Logic/ChessBishop.h"
#include "Chess/ChessPieces/Logic/ChessKing.h"
#include "Chess/ChessPieces/Logic/ChessKnight.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "Chess/ChessPieces/Logic/ChessQueen.h"
#include "Chess/ChessPieces/Logic/ChessRook.h"


UChessPiece* UChessPiecesFactory::GenerateChessPiece(const EFigure FigureType, UObject* Initializer)
{
	switch (FigureType)
	{
	case EFigure::Pawn:
		return NewObject<UChessPawn>(Initializer);
	case EFigure::Rook:
		return NewObject<UChessRook>(Initializer);
	case EFigure::Knight:
		return NewObject<UChessKnight>(Initializer);
	case EFigure::Bishop:
		return NewObject<UChessBishop>(Initializer);
	case EFigure::Queen:
		return NewObject<UChessQueen>(Initializer);
	case EFigure::King:
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
	case EFigure::Pawn:
		{
			const UChessPawn* OriginalPawn = Cast<UChessPawn>(Original);
			return DuplicateObject(OriginalPawn, Initializer);
		}
	case EFigure::Rook:
		{
			const UChessRook* OriginalRook = Cast<UChessRook>(Original);
			return DuplicateObject(OriginalRook, Initializer);
		}
	case EFigure::Knight:
		{
			const UChessKnight* OriginalKnight = Cast<UChessKnight>(Original);
			return DuplicateObject(OriginalKnight, Initializer);
		}
	case EFigure::Bishop:
		{
			const UChessBishop* OriginalBishop = Cast<UChessBishop>(Original);
			return DuplicateObject(OriginalBishop, Initializer);
		}
	case EFigure::Queen:
		{
			const UChessQueen* OriginalQueen = Cast<UChessQueen>(Original);
			return DuplicateObject(OriginalQueen, Initializer);
		}
	case EFigure::King:
		{
			const UChessKing* OriginalKing = Cast<UChessKing>(Original);
			return DuplicateObject(OriginalKing, Initializer);
		}
	default:
		UE_LOG(LogTemp, Error, TEXT("Initializing piece with default type!"))
		return NewObject<UChessPiece>(Initializer);
	}
}
