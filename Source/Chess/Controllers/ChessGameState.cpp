#include "ChessGameState.h"


void AChessGameState::Initialize()
{
	RulesController = NewObject<UChessRulesController>();
}

void AChessGameState::BroadcastTurnEnded(EColor Color) const
{
	TurnEndedEvent.Broadcast(Color);
}

void AChessGameState::EndTurn()
{
	const EColor CurrentPlayerColor = CurrentPlayer;
	const EColor EnemyPlayer = CurrentPlayer == EColor::Black ? EColor::White : EColor::Black;
	if (CurrentPlayer == EColor::White)
	{
		CurrentPlayer = EColor::Black;
	}
	else
	{
		CurrentPlayer = EColor::White;
	}
	const ECheckmateStatus Status = RulesController->GetCheckmateStatusForPlayer(Chessboard, EnemyPlayer, ChessboardController);
	const FString Value = UEnum::GetValueAsString(Status);
	BroadcastTurnEnded(CurrentPlayerColor);
	UE_LOG(LogTemp, Log, TEXT("Check mate status is %s"), *FString(Value));
}

AChessGameState::FTurnEnded& AChessGameState::OnTurnEnded()
{
	return TurnEndedEvent;
}

EColor AChessGameState::GetCurrentPlayer()
{
	return CurrentPlayer;
}