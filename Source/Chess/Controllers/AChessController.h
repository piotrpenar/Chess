// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
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
	void CreateChessPiece();
	void CreateFigures(const EColor FigureColor);
	virtual void BeginPlay() override;
	UChessPiece* GenerateChessPiece(const EFigureType Figure);

	UPROPERTY(EditAnywhere)
	UChessData* ChessData;
	
	UPROPERTY(EditAnywhere)
	AActor* ChessBoardOrigin;

private:
	UPROPERTY()
	TArray<F2DBoardArray> Board;

	UPROPERTY()
	TMap<EFigureType, UChessPiece*> FigureTypeMap;
	FTransform GetChessBoardTransform() const; 
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
	
};
