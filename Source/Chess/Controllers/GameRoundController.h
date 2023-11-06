// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCIController.h"
#include "Chess/Interfaces/GameLoopProvider.h"
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

	UPROPERTY()
	FRoundSettings RoundSettings;

	UPROPERTY()
	FPlayerChessState WhitePlayerState;
	UPROPERTY()
	FPlayerChessState BlackPlayerState;

	FPlayerChessState* CurrentPlayerState;
	
	float WhitePlayerTimeRemaining;
	float BlackPlayerTimeRemaining;
	bool bIsTimerEnabled;
	EColor CurrentPlayerColor;

	UPROPERTY()
	UUCIController* UCIController;
	

public:
	void Tick(float deltaTime);

	void InitializeCPUPlayer();
	void CPUMove(EColor NextPlayerColor);
	UFUNCTION()
	void RoundStarted();
	UFUNCTION()
	void OnTurnEnded(EColor NextPlayerColor);
	UFUNCTION()
	FPlayerChessState& GetPlayerState(EColor PlayerColor);
	FPlayerChessState& GetFirstPlayerState();
	FPlayerChessState& GetSecondPlayerState();
	FPlayerChessState& GetCurrentPlayerState() const;
	void InitializeRound(FRoundSettings NewRoundSettings);
	void SetUCIController(UUCIController* UciController);
	void ConnectToTurnEndedEvent(ITurnsProvider& TurnsProvider);
};
