#pragma once
#include "Chess/Enums/Player.h"
#include "ChessGameData.generated.h"

UCLASS()
class UChessGameData : public UObject
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadWrite)
	FString PlayerOneName;
	UPROPERTY(BlueprintReadWrite)
	FString PlayerTwoName;
public:
	UFUNCTION(BlueprintGetter)
	const FString& GetPlayerName(EPlayer Player);
	
};
