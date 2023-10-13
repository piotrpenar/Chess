// Fill out your copyright notice in the Description page of Project Settings.


#include "UCIController.h"

UUCIController::~UUCIController()
{
	if(StockfishProcess)
	{
		StockfishProcess->Stop();
		StockfishProcess.Reset();
	}
}

FString UUCIController::GenerateFenGameState()
{
	return ChessboardController->GetChessboardFEN();
}

void UUCIController::SearchForBestMove(EColor Color)
{
	//TODO: Implement
}

void UUCIController::ResetStockfishPointer()
{
	if (StockfishProcess)
	{
		StockfishProcess->Stop();
		StockfishProcess.Reset();
	}
}

void UUCIController::Initialize(UChessboardController* NewChessboardController, FString NewStockfishFilePath)
{
	ChessboardController = NewChessboardController;
	if(FPlatformProcess::CreatePipe(StockfishPipeRead, StockfishPipeWrite))
	{
		UE_LOG(LogTemp, Display, TEXT("Created pipe"));
	}
	FString CombinedPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectPluginsDir(),NewStockfishFilePath));
	UE_LOG(LogTemp, Display, TEXT("Stockfish path: %s"), *CombinedPath);
	ChessboardController = NewChessboardController;
	
	ResetStockfishPointer();
	StockfishProcess = MakeUnique<FInteractiveProcess>(CombinedPath, TEXT(""), false);
	StockfishProcess->OnOutput().BindUFunction(this, TEXT("OnOutput"));
	StockfishProcess->OnCanceled().BindUFunction(this, TEXT("OnCanceled"));
	StockfishProcess->OnCompleted().BindUFunction(this, TEXT("OnCompleted"));
	StockfishProcess->SendWhenReady(TEXT("uci\n"));
	StockfishProcess->Launch();

	bool bIsRunning = StockfishProcess->IsRunning();
	UE_LOG(LogTemp, Display, TEXT("Stockfish running: %d"),bIsRunning);
	//TODO: Implement
	//TODO: Implement

		 
	IConsoleCommand* Command = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("UCI.TestCommand"),
		TEXT("Test command for UCI Connection"),
		FConsoleCommandDelegate::CreateUObject(this, &UUCIController::TestCommand),
		ECVF_Cheat
	);
}

void UUCIController::OnOutput(const FString& Output)
{
	//StockfishProcess->
	UE_LOG(LogTemp, Display, TEXT("Stockfish output: %s"),*Output);
}
void UUCIController::OnCanceled()
{
	UE_LOG(LogTemp, Display, TEXT("Stockfish canceled"));
	//TODO: Implement
}

void UUCIController::OnCompleted()
{
	UE_LOG(LogTemp, Display, TEXT("Stockfish completed"));
	//TODO: Implement
}

void UUCIController::TestCommand()
{
	UE_LOG(LogTemp, Display, TEXT("Starting test command"));
	StockfishProcess->SendWhenReady(TEXT("isready\n"));
}
