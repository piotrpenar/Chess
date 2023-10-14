#pragma once
#include "CoreMinimal.h"
#include "ChessGameState.h"
#include "Chess/Controllers/ChessRulesController.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "Chess/Utils/RoundSettings.h"
#include "GameFramework/GameMode.h"
#include "ChessGameMode.generated.h"

UCLASS(Blueprintable)
class CHESS_API AChessGameMode final : public AGameMode, public ITurnsProvider
{
	GENERATED_BODY()
	
	DECLARE_DERIVED_EVENT(AChessGameMode, ITurnsProvider::FTurnEnded, FTurnEndedForPlayerEvent);
	DECLARE_MULTICAST_DELEGATE(FTurnEndedEvent);

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
	
	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FTurnEndedForPlayerEvent TurnEndedForPlayerEvent;

	UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	FTurnEndedEvent TurnEndedEvent;
	
	virtual void EndTurn() override;
	void SetMovementProvider(TScriptInterface<IMovementRulesProvider> MovementRulesProviderReference);
	
	UFUNCTION(BlueprintGetter)
	FRoundSettings GetRoundSettings() const;
	UFUNCTION(BlueprintSetter)
	void SetRoundSettings(const FRoundSettings& NewRoundSettings);

};
