#include "ChessGameState.h"

void AChessGameState::CreateChessboard()
{
	if (!Chessboard)
	{
		Chessboard = NewObject<UChessboard>();
	}
}

UChessboard* AChessGameState::GetChessboard() const
{
	return Chessboard;
}

EColor AChessGameState::GetCurrentPlayer() const
{
	return CurrentPlayer;
}

void AChessGameState::SetCurrentPlayer(const EColor Color)
{
	CurrentPlayer = Color;
}