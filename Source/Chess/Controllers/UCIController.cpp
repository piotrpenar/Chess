// Fill out your copyright notice in the Description page of Project Settings.


#include "UCIController.h"

#include "Chess/Helpers/FENNotationHelper.h"

UUCIController::~UUCIController()
{
	if (StockfishProcess)
	{
		StockfishProcess->Stop();
		StockfishProcess.Reset();
	}
}

FString UUCIController::GenerateFenGameState(const EColor Color) const
{
	FString BoardFenString = FenNotationHelper->GenerateFENNotation();
	BoardFenString.Append(Color == EColor::White ? " w" : " b");
	return BoardFenString;
}

void UUCIController::OnMoveSelected(FString MoveString)
{
	FString ExtractedMove;
	MoveString.Split(" ", nullptr, &ExtractedMove);
	if (ExtractedMove.IsEmpty())
	{
		return;
	}
	const FIntPoint OriginalPos = FIntPoint(ExtractedMove[0] - 'a', ExtractedMove[1] - '1');
	const FIntPoint TargetPos = FIntPoint(ExtractedMove[2] - 'a', ExtractedMove[3] - '1');
	UChessPiece* OriginalPiece = Chessboard->GetPieceAtPosition(OriginalPos);
	UChessPiece* TargetPiece = Chessboard->GetPieceAtPosition(TargetPos);
	TArray<FMove> ValidSpecialMoves = Chessboard->GetMovementRuleProvider()->GetValidSpecialMoves(OriginalPiece);
	const FMove* SpecialMove = ValidSpecialMoves.FindByPredicate([TargetPos](const FMove& CurrentMove)
	{
		return CurrentMove.TargetPosition == TargetPos;
	});
	if(SpecialMove && SpecialMove->MoveType == EMoveType::PawnPromotion)
	{
		EFigure TargetFigure = UFENNotationHelper::GetFigureFromChar(ExtractedMove[4]);
		//TODO: Do something with Target Figure
	}
	MoveExecutor->ExecutePlayerMove(FMove(OriginalPiece, TargetPos, TargetPiece, SpecialMove == nullptr ? EMoveType::Standard : SpecialMove->MoveType));
}

void UUCIController::SearchForBestMove(EColor Color)
{
	EnqueueStockfishCommand(TEXT("setpos fen ") + GenerateFenGameState(Color));
	EnqueueStockfishCommand(TEXT("go") + AdditionalGoSettings);
}

void UUCIController::ResetStockfishPointer()
{
	if (StockfishProcess)
	{
		StockfishProcess->Stop();
		StockfishProcess.Reset();
	}
}

void UUCIController::InitializeStockfishProcess(FString CombinedPath)
{
	ResetStockfishPointer();
	StockfishProcess = MakeUnique<FInteractiveProcess>(CombinedPath, TEXT(""), false);
	StockfishProcess->OnOutput().BindUFunction(this, TEXT("OnOutput"));
	StockfishProcess->OnCanceled().BindUFunction(this, TEXT("OnCanceled"));
	StockfishProcess->OnCompleted().BindUFunction(this, TEXT("OnCompleted"));
	StockfishProcess->Launch();
}

void UUCIController::SendCommand(const FString& Message, const bool bWaitForResult)
{
	UE_LOG(LogTemp, Display, TEXT("Sending message to stockfish: %s"), *Message);
	StockfishProcess->SendWhenReady(Message + "\n");
	if(bWaitForResult)
	{
		bStockfishIsBusy = true;
	}
}

void UUCIController::EnqueueStockfishCommand(const FString& Message,const bool bWaitForResult)
{
	UE_LOG(LogTemp, Display, TEXT("Enqueuing message: %s"), *Message);
	StockfishInputQueue.Enqueue(TPair<FString,bool>(Message,bWaitForResult));
}

void UUCIController::InitializeStockfishSettings(const int SkillLevel, const int Depth, const int Time)
{
	EnqueueStockfishCommand(TEXT("setoption name Skill Level value ") + FString::FromInt(SkillLevel));
	AdditionalGoSettings = TEXT(" depth ") + FString::FromInt(Depth) + TEXT(" movetime ") + FString::FromInt(Time);
}

void UUCIController::Tick(float DeltaTime)
{
	if(!bStockfishIsBusy && !StockfishInputQueue.IsEmpty())
	{
		TPair<FString,bool> Message;
		StockfishInputQueue.Dequeue(Message);
		SendCommand(Message.Key,Message.Value);
	}
}

FString UUCIController::GenerateStockfishPath(FString NewStockfishFilePath)
{
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectPluginsDir(), NewStockfishFilePath));
}

void UUCIController::SetInitialConfig()
{
	EnqueueStockfishCommand(TEXT("uci"),true);
	EnqueueStockfishCommand(TEXT("setoption name Ponder value false"));
	EnqueueStockfishCommand(TEXT("position startpos"));
}

void UUCIController::Initialize(UChessboard* NewChessboard, TScriptInterface<IMoveExecutor> NewMoveExecutor, UChessData* NewChessData)
{
	Chessboard = NewChessboard;
	MoveExecutor = NewMoveExecutor;
	ChessData = NewChessData;
	FenNotationHelper = NewObject<UFENNotationHelper>();
	FenNotationHelper->Initialize(Chessboard);

	const FString ExecutablePath = GenerateStockfishPath(ChessData->GetStockfishPath());

	InitializeStockfishProcess(ExecutablePath);
	SetInitialConfig();
	MoveSelected.AddDynamic(this, &UUCIController::OnMoveSelected);
}

void UUCIController::SetCPUDifficulty(int Difficulty)
{
	const FCPUDifficultyDefinition SkillLevel = ChessData->GetCPUDifficulties()[Difficulty];
	InitializeStockfishSettings(SkillLevel.StockfishLevel, SkillLevel.StockfishDepth, SkillLevel.StockfishTime);
}

void UUCIController::OnOutput(FString& Output)
{
	if(Output.Contains(TEXT("uciok")))
	{
		bStockfishIsBusy = false;
	}
	if (Output.Contains(TEXT("bestmove")))
	{
		UE_LOG(LogTemp, Display, TEXT("Stockfish output: %s"), *Output);
		if (!MoveSelected.IsBound())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute move: %s"), *Output);
			return;
		}
		MoveSelected.Broadcast(Output);
		bStockfishIsBusy = false;
	}
}

void UUCIController::OnCanceled()
{
	UE_LOG(LogTemp, Error, TEXT("Stockfish canceled"));
}

void UUCIController::OnCompleted()
{
	UE_LOG(LogTemp, Error, TEXT("Stockfish completed"));
}

void UUCIController::TestCommand() const
{
	UE_LOG(LogTemp, Display, TEXT("Starting test command"));
	StockfishProcess->SendWhenReady(TEXT("isready\n"));
}
