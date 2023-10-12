// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Enums/Color.h"
#include "Chess/Enums/PlayerType.h"
#include "RoundSettings.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CHESS_API FRoundSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EColor FirstPlayerColor;
	UPROPERTY(BlueprintReadWrite)
	EPlayerType SecondPlayerType;
	UPROPERTY(BlueprintReadWrite)
	int RoundTime;
	UPROPERTY(BlueprintReadWrite)
	int CPUDifficulty;
};
