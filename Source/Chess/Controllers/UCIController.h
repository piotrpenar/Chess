// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Enums/Color.h"
#include "UObject/Object.h"
#include "UCIController.generated.h"

/**
 * 
 */
UCLASS()
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
class CHESS_API UUCIController : public UObject
{
	GENERATED_BODY()

private: 
	int StockfishPID;
	FString StockfishFilePath;

	UPROPERTY()
	UChessboardController* ChessboardController;

public:
	void GenerateBoardState();
	void SearchForBestMove(EColor Color);
	void Initialize(UChessboardController* NewChessboardController, FString NewStockfishFilePath);
};
