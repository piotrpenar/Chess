// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigure.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "UObject/Interface.h"
#include "Chessboard.generated.h"

UCLASS()
class CHESS_API UChessboard final : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	AActor* ChessBoardOrigin;
	UPROPERTY()
	TArray<F2DBoardArray> Board;

	bool bIsSimulation;
public:
	void Initialize(UChessData* NewChessData, AActor* NewChessBoardOrigin);
	UChessPiece* GetPieceAtPosition(FVector2D BoardPosition);
	FTransform BoardToWorldTransform(const int X, const int Y) const;
	FTransform BoardToWorldTransform(FVector2D Position) const;
	void SetPieceAtPosition(const FVector2D Position, UChessPiece* ChessPiece);
	void GenerateEmptyBoard();
	FTransform GetChessBoardTransform() const;
	TArray<UChessPiece*> GetAllPiecesOfColor(const EColor Color);
	UChessPiece* GetChessPiece(const EFigure Figure, const EColor Color);
	void SetAsSimulated(UChessboard* OriginalBoard, TScriptInterface<IMovementVerifier> SimulatedMovementVerifier);
};
