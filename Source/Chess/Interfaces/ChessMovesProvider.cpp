#include "ChessMovesProvider.h"
#include "Chess/Utils/FMove.h"

bool IChessMovesProvider::IsValidMove(const FIntPoint Position, UObject* ChessPiece)
{
	return false;
}

TArray<FMove> IChessMovesProvider::GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IChessMovesProvider::GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IChessMovesProvider::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	return {};
}
