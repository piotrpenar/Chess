#pragma once
#include "Chess/Utils/FMove.h"

#include "ChessMovesHelper.generated.h"

UCLASS()
class UChessMovesHelper final : public UObject
{
	GENERATED_BODY();
public:
	static const TArray<FMove> GetValidMovesFromPositions(const TArray<FVector2D> Positions,const TArray<F2DBoardArray>* Board,const EColor Color);
	static const TArray<FMove> GetValidMovesFromDirections(const TArray<FVector2D> Directions,const TArray<F2DBoardArray>* Board,const EColor Color);
};
