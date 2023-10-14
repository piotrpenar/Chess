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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveSelected, FString, MoveString);

UCLASS()
// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
class CHESS_API UUCIController : public UObject
{
	GENERATED_BODY()

private: 
	TUniquePtr<FInteractiveProcess> StockfishProcess;
	UPROPERTY()
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

	TQueue<TPair<FString,bool>> StockfishInputQueue;
	UPROPERTY()
	bool bStockfishIsBusy = false;
	UPROPERTY(BlueprintAssignable)
	FMoveSelected MoveSelected;
	UPROPERTY()
	FString StockfishMoveToExecute;

	~UUCIController();

public:
	FString GenerateFenGameState(EColor Color) const;
	UFUNCTION()
	void OnMoveSelected(FString MoveString);
	void SearchForBestMove(EColor Color);
	void ResetStockfishPointer();
	void InitializeStockfishProcess(FString CombinedPath);
	void SendCommand(const FString& Message, bool bWaitForResult);
	void EnqueueStockfishCommand(const FString& Message, const bool bWaitForResult = false);
	void InitializeStockfishSettings(int SkillLevel, int Depth, int Time);
	void Tick(float DeltaTime);
	static FString GenerateStockfishPath(FString NewStockfishFilePath);
	void SetInitialConfig();
	void Initialize(UChessboard* NewChessboard, TScriptInterface<IMoveExecutor> NewMoveExecutor, UChessData* NewChessData);
	void SetCPUDifficulty(int Difficulty);
	UFUNCTION()
	void OnOutput(FString& Output);
	UFUNCTION()
	static void OnCanceled();
	UFUNCTION()
	static void OnCompleted();
	UFUNCTION(Exec, Category = "ExecFunctions")
	void TestCommand() const;
	

};
