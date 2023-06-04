#include "ChessGameData.h"

const FString& UChessGameData::GetPlayerName(const EPlayer Player)
{
	switch (Player)
	{
	case EPlayer::First:
		return PlayerOneName;
	case EPlayer::Second:
		return PlayerTwoName;
	default:
		return FString("None");
	}
}
