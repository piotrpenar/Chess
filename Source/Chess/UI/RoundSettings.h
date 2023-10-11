// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Enums/Color.h"
#include "Chess/Enums/PlayerType.h"
#include "UObject/Object.h"
#include "RoundSettings.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API URoundSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	EColor FirstPlayerColor;
	UPROPERTY(BlueprintReadWrite)
	EPlayerType SecondPlayerType;
	UPROPERTY(BlueprintReadWrite)
	int RoundTime;
	UPROPERTY(BlueprintReadWrite)
	int CPUDifficulty;
	
};
