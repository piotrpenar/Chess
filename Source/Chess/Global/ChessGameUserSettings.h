#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ChessGameUserSettings.generated.h"

UCLASS(config=GameUserSettings)
class CHESS_API UChessGameUserSettings final : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static UChessGameUserSettings* GetChessGameUserSettings();
	
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetVolume() const { return Volume; }
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetVolume(const float Value) { Volume = Value;}
	
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetCameraYInverted() const { return bCameraInvertedY; }
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCameraYInverted(const bool bValue) { bCameraInvertedY = bValue;}

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;
	void ApplyVolume() const;

private:
	UPROPERTY(Config,BlueprintGetter=GetVolume, BlueprintSetter=SetVolume)
	float Volume = 1;
	UPROPERTY(Config,BlueprintGetter=GetCameraYInverted, BlueprintSetter=SetCameraYInverted)
	bool bCameraInvertedY = false;

};
