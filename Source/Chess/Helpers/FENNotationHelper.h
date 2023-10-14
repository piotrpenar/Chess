// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/BaseClasses/ChessboardBase.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/2DBoardArray.h"
#include "UObject/Object.h"
#include "FENNotationHelper.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UFENNotationHelper : public UObject
{
	GENERATED_BODY()

	int BoardSize = 8;

	inline static TMap<FString, EFigure> FENCharToFigureMap = {
		{TEXT("P"), EFigure::Pawn},
		{TEXT("R"), EFigure::Rook},
		{TEXT("N"), EFigure::Knight},
		{TEXT("B"), EFigure::Bishop},
		{TEXT("Q"), EFigure::Queen},
		{TEXT("K"), EFigure::King},
	};

	UPROPERTY()
	UChessboardBase* Chessboard;
	
public:
	void Initialize(UChessboardBase* ChessboardBase);
	FString GenerateFENNotation() const;
	static FString GetCharFromFigure(const EFigure Figure);
	static EFigure GetFigureFromChar(const TCHAR& Char);
	static EFigure GetFigureFromString(const FString& Char);
	static FString GetPieceFENNotation(UChessPiece* Piece);
};
