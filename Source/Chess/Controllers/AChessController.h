// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/UChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "AChessController.generated.h"

/**
 * 
*/
UCLASS(Blueprintable)
class CHESS_API AChessController : public AActor 
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
	FTransform GenerateChessPieceTransform(int TargetRow, int TargetColumn, EColor Color) const;
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
