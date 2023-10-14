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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString SettingName = "Default";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int EloRating = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int StockfishLevel = 0 ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int StockfishDepth = 16;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int StockfishTime = 1000;
};
