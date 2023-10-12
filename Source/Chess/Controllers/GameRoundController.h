// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCIController.h"
#include "Chess/Utils/PlayerChessState.h"
#include "Chess/Utils/RoundSettings.h"
#include "UObject/Object.h"
#include "GameRoundController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UGameRoundController : public UObject
{
	GENERATED_BODY()

	FRoundSettings RoundSettings;

	FPlayerChessState WhitePlayerState;
	FPlayerChessState BlackPlayerState;
	
	FPlayerChessState* CurrentPlayerState;
	
	float WhitePlayerTimeRemaining;
	float BlackPlayerTimeRemaining;
	bool bIsTimerEnabled;
	EColor CurrentPlayerColor;

	UPROPERTY()
	UUCIController* UCIController;
	

public:
	void Update(float deltaTime);

	void InitializeCPUPlayer();
	void OnTurnEnded(EColor NextPlayerColor);
	FPlayerChessState& GetPlayerState(EColor PlayerColor);
	FPlayerChessState& GetFirstPlayerState();
	FPlayerChessState& GetSecondPlayerState();
	void InitializeRound(FRoundSettings NewRoundSettings);
	void SetUCIController(UUCIController* UciController);
};
