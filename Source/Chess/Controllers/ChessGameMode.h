#pragma once
#include "CoreMinimal.h"
#include "ChessGameState.h"
#include "ChessRulesController.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "GameFramework/GameMode.h"
#include "ChessGameMode.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessGameMode final : public AGameMode, public ITurnsProvider
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UChessRulesController* RulesController;

	UPROPERTY()
	AChessGameState* ChessGameState;

	UPROPERTY()
	TScriptInterface<IMovementRulesProvider> MovementRulesProvider;

	FTurnEnded TurnEndedEvent;

public:
	void Initialize();
	virtual void BeginPlay() override;
	virtual void EndTurn() override;
	void BroadcastTurnEnded(EColor Color) const;
	void SetMovementProvider(TScriptInterface<IMovementRulesProvider> MovementRulesProviderReference);

	DECLARE_DERIVED_EVENT(AChessGameState, ITurnsProvider::FTurnEnded, FTurnEndedEvent);

	virtual FTurnEnded& OnTurnEnded() override;
};
