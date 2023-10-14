// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRoundController.h"

void UGameRoundController::Update(float deltaTime)
{
	if(!bIsTimerEnabled)
	{
		return;
	}
	if(this->CurrentPlayerState->bHasTimeLimit)
	{
		this->CurrentPlayerState->TimeRemaining -= deltaTime;
		if(this->CurrentPlayerState->TimeRemaining <= 0)
		{
			//TODO: Gameover
		}
	}
}

void UGameRoundController::InitializeCPUPlayer()
{
	
}

void UGameRoundController::OnTurnEnded(EColor NextPlayerColor)
{
	FPlayerChessState& NextPlayerState = GetPlayerState(NextPlayerColor);
	if(NextPlayerState.PlayerType == EPlayerType::CPU)
	{
		//TODO: Block user input
		UCIController->SearchForBestMove(NextPlayerColor);
	}
	else
	{
		//TODO: Swtitch cameras and config
	}
	this->CurrentPlayerState = &GetPlayerState(NextPlayerColor);
}

FPlayerChessState& UGameRoundController::GetPlayerState(const EColor PlayerColor){
	return PlayerColor == EColor::White ? WhitePlayerState : BlackPlayerState;
}

FPlayerChessState& UGameRoundController::GetFirstPlayerState()
{
	return this->RoundSettings.FirstPlayerColor == EColor::White ? WhitePlayerState : BlackPlayerState;
}

FPlayerChessState& UGameRoundController::GetSecondPlayerState()
{
	return this->RoundSettings.FirstPlayerColor == EColor::Black ? WhitePlayerState : BlackPlayerState;
}

void UGameRoundController::InitializeRound(FRoundSettings NewRoundSettings)
{
	this->RoundSettings = NewRoundSettings;

	if(this->RoundSettings.FirstPlayerColor == EColor::Unspecified)
	{
		const bool bRandBool = FMath::RandBool();
		this->RoundSettings.FirstPlayerColor = bRandBool ? EColor::White : EColor::Black;
	}

	WhitePlayerState.PlayerColor = EColor::White;
	BlackPlayerState.PlayerColor = EColor::Black;
	
	FPlayerChessState& FirstPlayerState= GetFirstPlayerState();
	FPlayerChessState& SecondPlayerState= GetSecondPlayerState();

	FirstPlayerState.PlayerType = EPlayerType::Human;
	SecondPlayerState.PlayerType = this->RoundSettings.SecondPlayerType;

	const bool bHumansHaveTimeLimit = NewRoundSettings.RoundTime >= 0;
	
	FirstPlayerState.bHasTimeLimit = bHumansHaveTimeLimit;
	SecondPlayerState.bHasTimeLimit = bHumansHaveTimeLimit && this->RoundSettings.SecondPlayerType == EPlayerType::Human;

	if(SecondPlayerState.PlayerType == EPlayerType::CPU)
	{
		InitializeCPUPlayer();
	}
}

void UGameRoundController::SetUCIController(UUCIController* UciController)
{
	this->UCIController = UciController;
}
