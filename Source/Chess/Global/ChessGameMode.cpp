#include "ChessGameMode.h"

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

void AChessGameMode::BroadcastTurnEnded(const EColor Color) const
{
	TurnEndedForPlayerEvent.Broadcast(Color);
	TurnEndedEvent.Broadcast();
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
	BroadcastTurnEnded(CurrentPlayerColor);
}

FRoundSettings AChessGameMode::GetRoundSettings() const
{
	return this->RoundSettings;
}

void AChessGameMode::SetRoundSettings(const FRoundSettings& NewRoundSettings)
{
	RoundSettings = NewRoundSettings;
}
