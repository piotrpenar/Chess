#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "ChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()

public:
	virtual EFigure GetFigureType() override;
	virtual TArray<FMove> GetAvailableMoves() override;
	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition) override;
	bool IsValidPassantTarget() const;
	void BindToTurnEndedEvent(ITurnsProvider* TurnsProvider);

private:
	UPROPERTY()
	bool bHasDoubleMoved;

	TArray<FIntPoint> GetPossiblePositions() const;
	void HandleTurnEnded(EColor& CurrentColor);
	bool HasDoubleMoved(FIntPoint Position) const;
};
