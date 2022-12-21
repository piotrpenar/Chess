#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Helpers/ChessMovesHelper.h"
#include "ChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()
	
	FChessMovesData GenerateMovesData();
	TArray<FVector2D> GetPossibleMoves();
	bool bHasMoved;
	
public:
	virtual EFigure GetFigureType() override;
	virtual TArray<FMove> GetAvailableMoves() override;
	virtual void MoveToPosition(FVector2D Position) override;
	
};
