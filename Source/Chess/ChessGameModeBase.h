// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EColor.h"
#include "EPawnType.h"
#include "ChessPieces/UChessPiece.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGameState() override;
	static UChessPiece* GenerateChessPiece(const EPawnType Figure);
	void CreateFigures(const TArray<EPawnType> Pawns, TArray<EPawnType> Men, const EColor Color);
	void CreateChessPiece();

private:
	TArray<TArray<UChessPiece*>> Board;
	int BoardSize = 8;
	void GenerateChessRow(TArray<EPawnType> Figures, const EColor Color, const int TargetRow);
	const TArray<EPawnType> Pawns = {
		EPawnType::Pawn, EPawnType::Pawn, EPawnType::Pawn, EPawnType::Pawn, EPawnType::Pawn, EPawnType::Pawn,
		EPawnType::Pawn, EPawnType::Pawn
	};
	const TArray<EPawnType> Men = {
		EPawnType::Rook, EPawnType::Knight, EPawnType::Bishop, EPawnType::King, EPawnType::Queen, EPawnType::Bishop,
		EPawnType::Knight, EPawnType::Rook
	};
};
