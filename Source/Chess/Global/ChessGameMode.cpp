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
	UE_LOG(LogTemp,Warning,TEXT("Turn ended for player %s"),*UEnum::GetValueAsString(Color));
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
	const ECheckmateStatus Status = RulesController->GetCheckmateStatusForPlayer(ChessGameState->GetChessboard(), EnemyPlayer, MovementRulesProvider.GetInterface());
	const FString Value = UEnum::GetValueAsString(Status);
	if (Status == ECheckmateStatus::Checkmate || Status == ECheckmateStatus::Stalemate)
	{
		EndGame(Status, Status == ECheckmateStatus::Stalemate ? EColor::Unspecified : CurrentPlayerColor);
		return;
	}
	BroadcastTurnEnded(CurrentPlayerColor);
	ChessGameState->SetCurrentPlayer(EnemyPlayer);
}

void AChessGameMode::StartGame()
{
	UE_LOG(LogTemp,Warning,TEXT("Game started!"));
	GameStartedEvent.Broadcast();
	//TODO: Unblock input
}

void AChessGameMode::EndGame(ECheckmateStatus Result, EColor Winner)
{
	//TODO: DO SOMETHING WITH THE RESULT
	GameEndedEvent.Broadcast(Winner);
}

FRoundSettings AChessGameMode::GetRoundSettings() const
{
	return this->RoundSettings;
}

void AChessGameMode::SetRoundSettings(const FRoundSettings& NewRoundSettings)
{
	RoundSettings = NewRoundSettings;
}

FTurnEndedForPlayerEvent& AChessGameMode::OnTurnEndedForPlayerEvent()
{
	return TurnEndedForPlayerEvent;
}

FTurnEndedEvent& AChessGameMode::OnTurnEndedEvent()
{
	return TurnEndedEvent;
}

FGameStartedEvent& AChessGameMode::OnGameStartedEvent()
{
	return GameStartedEvent;
}

FGameEndedEvent& AChessGameMode::OnGameEndedEvent()
{
	return GameEndedEvent;
}

