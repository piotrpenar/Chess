// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPUDifficultyDefinition.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CHESS_API FCPUDifficultyDefinition
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString SettingName;
	UPROPERTY(BlueprintReadWrite)
	int EloRating;
	UPROPERTY(BlueprintReadWrite)
	int StockfishLevel;
	UPROPERTY(BlueprintReadWrite)
	int StockfishDepth;
	UPROPERTY(BlueprintReadWrite)
	int StockfishTime;
};
