#include "ChessGameUserSettings.h"

UChessGameUserSettings* UChessGameUserSettings::GetChessGameUserSettings()
{
	return Cast<UChessGameUserSettings>(GetGameUserSettings());
}