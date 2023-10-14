// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Enums/Color.h"
#include "Chess/Enums/PlayerType.h"
#include "PlayerChessState.generated.h"

USTRUCT(Blueprintable)
struct CHESS_API FPlayerChessState
{
	GENERATED_BODY()

	UPROPERTY()
	EColor PlayerColor = EColor::Unspecified;
	UPROPERTY()
	EPlayerType PlayerType = EPlayerType::Unknown;
	UPROPERTY()
	bool bHasTimeLimit = false;
	UPROPERTY()
	float TimeRemaining = 0;
};
