// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Enums/Color.h"
#include "Chess/Global/ChessGameState.h"
#include "Chess/Helpers/FENNotationHelper.h"
#include "Chess/Interfaces/MoveExecutor.h"
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
	TUniquePtr<FInteractiveProcess> StockfishProcess;
	FString AdditionalGoSettings;

	UPROPERTY()
	UChessboard* Chessboard;
	UPROPERTY()
	AChessGameState* GameState;
	UPROPERTY()
	TScriptInterface<IMoveExecutor> MoveExecutor;
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	UFENNotationHelper* FenNotationHelper;

	~UUCIController();

public:
	FString GenerateFenGameState(EColor Color) const;
	FMove ExtractMoveFromString(const FString& String);
	void OnMoveSelected(FString MoveString);
	void SearchForBestMove(EColor Color) const;
	void ResetStockfishPointer();
	void InitializeStockfishProcess(FString CombinedPath);
	void SendStockfishCommand(const FString& Message) const;
	void InitializeStockfishSettings(int SkillLevel, int Depth, int Time);
	static FString GenerateStockfishPath(FString NewStockfishFilePath);
	void SetInitialConfig() const;
	void Initialize(UChessboard* NewChessboard, TScriptInterface<IMoveExecutor> NewMoveExecutor, UChessData* NewChessData);
	void SetCPUDifficulty(int Difficulty);
	UFUNCTION()
	void OnOutput(const FString& Output) const;
	UFUNCTION()
	static void OnCanceled();
	UFUNCTION()
	static void OnCompleted();
	UFUNCTION(Exec, Category = "ExecFunctions")
	void TestCommand() const;

	DECLARE_DELEGATE_OneParam(FMoveSelected, FString);
	FMoveSelected MoveSelected;
	

};
