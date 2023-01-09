#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/ChessboardMovementRulesBase.h"
#include "Simulation/SimulatedChessboard.h"
#include "ChessboardMovementRules.generated.h"

UCLASS()
class CHESS_API UChessboardMovementRules final : public UChessboardMovementRulesBase
{
	UPROPERTY()
	USimulatedChessboard* SimulatedChessboard;
public:
	GENERATED_BODY()
	void SetSimulatedChessboard(USimulatedChessboard* SimulatedChessboardReference);
	virtual bool IsValidMove(const FIntPoint Position, UObject* ChessPieceObject) override;
	bool CanMoveInSimulation(FIntPoint Position, UChessPiece* ChessPiece) const;
};
