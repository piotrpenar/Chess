#include "ChessGameUserSettings.h"

#include "AudioDevice.h"

UChessGameUserSettings* UChessGameUserSettings::GetChessGameUserSettings()
{
	return Cast<UChessGameUserSettings>(GetGameUserSettings());
}

void UChessGameUserSettings::ApplySettings(const bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
	ApplyVolume();
}

void UChessGameUserSettings::ApplyVolume() const
{
	const FAudioDeviceHandle AudioDevice = GEngine->GetMainAudioDevice();
	if(!AudioDevice.GetAudioDevice())
	{
		return;
	}
	AudioDevice.GetAudioDevice()->SetTransientPrimaryVolume(this->Volume); 
}
