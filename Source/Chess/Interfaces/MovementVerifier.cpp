#include "MovementVerifier.h"
#include "Chess/Utils/FMove.h"

bool IMovementVerifier::IsValidMove(const FIntPoint Position, UObject* ChessPiece)
{
	return false;
}

TArray<FMove> IMovementVerifier::GetValidMovesFromPositions(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementVerifier::GetValidMovesFromDirections(TArray<FIntPoint> Directions, UObject* ChessPiece)
{
	return {};
}

TArray<FMove> IMovementVerifier::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	return {};
}
