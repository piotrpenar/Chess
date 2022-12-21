#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessQueen.generated.h"

UCLASS()
class UChessQueen final : public UChessPiece
{
	GENERATED_BODY()
	
	FChessMovesData GenerateMovesData();
	TArray<FVector2D> GetPossibleDirections() const;
public:
	virtual EFigureType GetFigureType() override;
	virtual TArray<FMove> GetAvailableMoves() override;
};
