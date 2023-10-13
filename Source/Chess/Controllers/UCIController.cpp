// Fill out your copyright notice in the Description page of Project Settings.


#include "UCIController.h"

UUCIController::~UUCIController()
{
	if(this->StockfishProcess.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Closing Stockfish process"));
		FPlatformProcess::CloseProc(this->StockfishProcess);
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

void UUCIController::Initialize(UChessboardController* NewChessboardController, FString NewStockfishFilePath)
{
	ChessboardController = NewChessboardController;
	if(FPlatformProcess::CreatePipe(StockfishPipeRead, StockfishPipeWrite))
	{
		UE_LOG(LogTemp, Display, TEXT("Created pipe"));
	}
	StockfishProcess = FGenericPlatformProcess::CreateProc(NewStockfishFilePath.GetCharArray().GetData(), nullptr, true, false, false, nullptr, 0, nullptr, StockfishPipeWrite, StockfishPipeRead, nullptr);

	FGenericPlatformProcess::WritePipe(StockfishPipeWrite, "uci\n");
	FString response = FGenericPlatformProcess::ReadPipe(StockfishPipeRead);
	if(response.Len()>0)
	{
		UE_LOG(LogTemp, Display, TEXT("Stockfish response: %s"), *response);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Stockfish response is empty"));
	}
	
	//TODO: Implement
}
