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
	bool HasMoved();

private:
	TArray<FIntPoint> GetPossiblePositions();
	bool bHasMoved;
	bool bHasDoubleMoved;
	void HandleTurnEnded(EColor& CurrentColor);
	bool HasDoubleMoved(FIntPoint Position) const;
};
