#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Helpers/ChessMovesHelper.h"
#include "ChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()
public:
	virtual EFigureType GetFigureType() override { return EFigureType::Pawn;};
	virtual TArray<FMove> GetAvailableMoves() override;
	
private:
	bool bHasMoved;
	
	virtual void MoveToPosition() override;
};
