// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Enums/CheckmateStatus.h"
#include "Chess/Enums/Color.h"
#include "UObject/Interface.h"
#include "GameLoopProvider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameEndedEvent, EColor,Winner, ECheckmateStatus, Result);

UINTERFACE()
class UGameLoopProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IGameLoopProvider
{
	GENERATED_BODY()

public:
	
	virtual FGameStartedEvent& OnGameStartedEvent() = 0;
	virtual FGameEndedEvent& OnGameEndedEvent() = 0;
	virtual void StartGame() = 0 ;
	virtual void EndGame(ECheckmateStatus Result,EColor Winner) = 0;
};
