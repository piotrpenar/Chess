// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRoundController.h"

void UGameRoundController::Tick(float DeltaTime)
{
	if(UCIController != nullptr)
	{
		UCIController->Tick(DeltaTime);
	}
	
	if(!bIsTimerEnabled)
	{
		return;
	}
	if(this->CurrentPlayerState->bHasTimeLimit)
	{
		this->CurrentPlayerState->TimeRemaining -= DeltaTime;
		if(this->CurrentPlayerState->TimeRemaining <= 0)
		{
			//TODO: Gameover
		}
	}
}

void UGameRoundController::InitializeCPUPlayer()
{
	
}

void UGameRoundController::CPUMove(EColor NextPlayerColor)
{
	//TODO: Block user input
	UCIController->SearchForBestMove(NextPlayerColor);
}

void UGameRoundController::RoundStarted()
{
	if(WhitePlayerState.PlayerType == EPlayerType::CPU)
	{
		CPUMove(EColor::White);
	}
}

void UGameRoundController::OnTurnEnded(EColor PlayerColor)
{
	UE_LOG(LogTemp, Display, TEXT("Turn ended for player %s"), *UEnum::GetValueAsString(PlayerColor));
	CurrentPlayerColor = PlayerColor == EColor::White ? EColor::Black : EColor::White;
	FPlayerChessState& NextPlayerState = GetPlayerState(CurrentPlayerColor);
	if(NextPlayerState.PlayerType == EPlayerType::CPU)
	{
		CPUMove(CurrentPlayerColor);
	}
	this->CurrentPlayerState = &GetPlayerState(CurrentPlayerColor);
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

FPlayerChessState& UGameRoundController::GetCurrentPlayerState() const
{
	return *CurrentPlayerState;
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

	CurrentPlayerState = &WhitePlayerState;
}

void UGameRoundController::SetUCIController(UUCIController* UciController)
{
	this->UCIController = UciController;
}

void UGameRoundController::ConnectToTurnEndedEvent(ITurnsProvider& TurnsProvider)
{
	TurnsProvider.OnTurnEndedForPlayerEvent().AddDynamic(this, &UGameRoundController::OnTurnEnded);
}
