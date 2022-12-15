// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChessData.h"
#include "EColor.h"
#include "EFigureType.h"
#include "F2DBoardArray.h"
#include "ChessPieces/UChessPiece.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHESS_API AChessGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitializeChessPieces();
	virtual void BeginPlay() override;
	UChessPiece* GenerateChessPiece(const EFigureType Figure);
	void CreateFigures(const EColor FigureColor);
	void CreateChessPiece();

	UPROPERTY(EditAnywhere)
	UChessData* ChessData;

private:
	int BoardSize = 8;
	void GenerateChessRow(TArray<EFigureType> Figures, const EColor Color, const int TargetRow);
	const TArray<EFigureType> Pawns = {
		EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn,
		EFigureType::Pawn, EFigureType::Pawn
	};
	const TArray<EFigureType> Men = {
		EFigureType::Rook, EFigureType::Knight, EFigureType::Bishop, EFigureType::King, EFigureType::Queen, EFigureType::Bishop,
		EFigureType::Knight, EFigureType::Rook
	};
	
	UPROPERTY()
	TArray<F2DBoardArray> Board;

	UPROPERTY()
	TMap<EFigureType, UChessPiece*> FigureTypeMap;
};
