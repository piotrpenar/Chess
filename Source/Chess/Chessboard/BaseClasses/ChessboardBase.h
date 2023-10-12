// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Interfaces/MovementRulesProvider.h"
#include "Chess/Utils/2DBoardArray.h"
#include "UObject/Object.h"
#include "ChessboardBase.generated.h"

UCLASS()
class CHESS_API UChessboardBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<F2DBoardArray> Board;
	UPROPERTY()
	TScriptInterface<IMovementRulesProvider> ChessboardMovementRules;
	int BoardSize = 8; 
	
	void GenerateEmptyBoard();

public:
	void Initialize(int NewChessboardSize);
	bool IsValidBoardPosition(const FIntPoint& Position) const;
	void DestroyChessPieceActors();
	void ResetChessboard();
	virtual void SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece);
	void MovePieceFromToPosition(UChessPiece* ChessPiece, FIntPoint FromPosition, FIntPoint ToPosition);
	UChessPiece* GetPieceAtPosition(FIntPoint BoardPosition);
	TArray<UChessPiece*> GetAllPiecesOfColor(const EColor Color) const;
	TArray<UChessPiece*> GetChessPieces(const EColor Color, const EFigure FigureType) const;
	FString GetBoardFENNotation();
	int GetBoardSize() const;
};
