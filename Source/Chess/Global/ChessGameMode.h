#pragma once
#include "CoreMinimal.h"
#include "ChessGameState.h"
#include "Chess/Controllers/ChessRulesController.h"
#include "Chess/Interfaces/GameLoopProvider.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "Chess/Utils/RoundSettings.h"
#include "GameFramework/GameMode.h"
#include "ChessGameMode.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessGameMode final : public AGameMode, public ITurnsProvider, public IGameLoopProvider
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UChessRulesController* RulesController;

	UPROPERTY()
	FRoundSettings RoundSettings;

	UPROPERTY()
	AChessGameState* ChessGameState;

	UPROPERTY()
	TScriptInterface<IMovementRulesProvider> MovementRulesProvider;

	
	void Initialize();
	void BroadcastTurnEnded(EColor Color) const;

protected:
	virtual void BeginPlay() override;
	
public:
	
	virtual void EndTurn() override;
	UFUNCTION(BlueprintCallable)
	virtual void StartGame() override;
	UFUNCTION(BlueprintCallable)
	virtual void EndGame(ECheckmateStatus Result,EColor Winner) override;
	
	void SetMovementProvider(TScriptInterface<IMovementRulesProvider> MovementRulesProviderReference);
	
	UFUNCTION(BlueprintCallable)
	FRoundSettings GetRoundSettings() const;
	UFUNCTION(BlueprintCallable)
	void SetRoundSettings(const FRoundSettings& NewRoundSettings);
	
	UPROPERTY(BlueprintAssignable)
	FTurnEndedForPlayerEvent TurnEndedForPlayerEvent;
	UPROPERTY(BlueprintAssignable)
	FTurnEndedEvent TurnEndedEvent;
	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FGameStartedEvent GameStartedEvent;
	UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	FGameEndedEvent GameEndedEvent;
	
	virtual FTurnEndedForPlayerEvent& OnTurnEndedForPlayerEvent() override;
	virtual FTurnEndedEvent& OnTurnEndedEvent() override;
	virtual FGameStartedEvent& OnGameStartedEvent() override;
	virtual FGameEndedEvent& OnGameEndedEvent() override;
};
