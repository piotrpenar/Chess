#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()

public:
	virtual EFigure GetFigureType() override;
	virtual TArray<FMove> GetAvailableMoves() override;
	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition) override;
	bool IsValidPassantTarget();

private:
	UPROPERTY()
	bool bHasDoubleMoved;

	TArray<FIntPoint> GetPossiblePositions();
	void HandleTurnEnded(EColor& CurrentColor);
	bool HasDoubleMoved(FIntPoint Position) const;
};
