#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessBishop.generated.h"

UCLASS()
class UChessBishop final : public UChessPiece
{
	GENERATED_BODY()
	
	FChessMovesData GenerateMovesData();
	TArray<FVector2D> GetPossibleDirections() const;
	
public:
	virtual EFigureType GetFigureType() override;;
	virtual TArray<FMove> GetAvailableMoves()  override;
};
