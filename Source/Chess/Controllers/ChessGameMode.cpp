﻿#include "ChessGameMode.h"

#include "Chess/Chessboard/ChessboardController.h"
#include "ChessRulesController.h"

void AChessGameMode::Initialize()
{
	ChessGameState = GetWorld()->GetGameState<AChessGameState>();
	RulesController = NewObject<UChessRulesController>();
}

void AChessGameMode::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
	ChessGameState->CreateChessboard();
}

void AChessGameMode::BroadcastTurnEnded(EColor Color) const
{
	TurnEndedEvent.Broadcast(Color);
}

void AChessGameMode::SetMovementProvider(const TScriptInterface<IMovementRulesProvider> MovementRulesProviderReference)
{
	MovementRulesProvider = MovementRulesProviderReference;
}

void AChessGameMode::EndTurn()
{
	const EColor CurrentPlayerColor = ChessGameState->GetCurrentPlayer();
	const EColor EnemyPlayer = CurrentPlayerColor == EColor::Black ? EColor::White : EColor::Black;
	ChessGameState->SetCurrentPlayer(EnemyPlayer);
	const ECheckmateStatus Status = RulesController->GetCheckmateStatusForPlayer(ChessGameState->GetChessboard(), EnemyPlayer, MovementRulesProvider.GetInterface());
	const FString Value = UEnum::GetValueAsString(Status);
	UE_LOG(LogTemp, Log, TEXT("Checkmate status is %s"), *FString(Value));
	BroadcastTurnEnded(CurrentPlayerColor);
}

AChessGameMode::FTurnEnded& AChessGameMode::OnTurnEnded()
{
	return TurnEndedEvent;
}
