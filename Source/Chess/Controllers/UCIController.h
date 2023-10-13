// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Enums/Color.h"
#include "UObject/Object.h"
#include "Misc/InteractiveProcess.h"
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
	FString StockfishFilePath;
	TUniquePtr<FInteractiveProcess> StockfishProcess;
	
	void* StockfishPipeRead;
	void* StockfishPipeWrite;

	UPROPERTY()
	UChessboardController* ChessboardController;
	
	
	~UUCIController();

public:
	FString GenerateFenGameState();
	void SearchForBestMove(EColor Color);
	void ResetStockfishPointer();
	void Initialize(UChessboardController* NewChessboardController, FString NewStockfishFilePath);
	UFUNCTION()
	void OnOutput(const FString& Output);
	UFUNCTION()
	void OnCanceled();
	UFUNCTION()
	void OnCompleted();
	//UFUNCTION(Exec, Category = "ExecFunctions")
	void TestCommand();
};
