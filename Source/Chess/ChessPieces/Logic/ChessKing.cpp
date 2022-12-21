#include "ChessKing.h"
#include "Chess/Helpers/ChessMovesHelper.h"


EFigureType UChessKing::GetFigureType()
{
	return EFigureType::King;
}

TArray<FVector2D> UChessKing::GetPossibleMoves() const
{
	return {
		BoardPosition + FVector2D(-1, -1),
		BoardPosition + FVector2D(-1, 0),
		BoardPosition + FVector2D(-1, 1),
		BoardPosition + FVector2D(0, 1),
		BoardPosition + FVector2D(1, 1),
		BoardPosition + FVector2D(1, 0),
		BoardPosition + FVector2D(1, -1),
		BoardPosition + FVector2D(0, -1),
	};
}

FChessMovesData UChessKing::GenerateMovesData()
{
	return FChessMovesData(GetPossibleMoves(), BoardProvider, Color, BoardPosition,this);
}


TArray<FMove> UChessKing::GetAvailableMoves()
{
	const FChessMovesData PossibleMovesData = GenerateMovesData();
	return UChessMovesHelper::GetValidMovesFromPositions(PossibleMovesData);
}
