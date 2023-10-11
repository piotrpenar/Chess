#pragma once
#include "..\Enums\ChessPlayer.h"
#include "ChessGameData.generated.h"

UCLASS(Blueprintable)
class UChessGameData : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintGetter=GetFirstPlayerName, BlueprintSetter=SetFirstPlayerName)
	FString PlayerOneName;
	UPROPERTY(BlueprintGetter=GetSecondPlayerName, BlueprintSetter=SetSecondPlayerName)
	FString PlayerTwoName;
public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	FString GetFirstPlayerName() { return PlayerOneName; };
	UFUNCTION(BlueprintCallable)
	void SetFirstPlayerName(const FString& Name) { PlayerOneName = Name; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	FString GetSecondPlayerName(){ return PlayerTwoName; };
	UFUNCTION(BlueprintCallable)
	void SetSecondPlayerName(const FString& Name) { PlayerTwoName = Name; }
	
};
