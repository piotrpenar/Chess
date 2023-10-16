#include "ChessController.h"

#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Highlight/ChessHighlighter.h"


AChessController::AChessController()
{
	PrimaryActorTick.bCanEverTick=true;
}

void AChessController::SetupGameRoundController()
{
	UE_LOG(LogTemp,Warning,TEXT("Configuring Round Controller!"));
	GameRoundController = NewObject<UGameRoundController>();
	if(GameMode->GetRoundSettings().SecondPlayerType == EPlayerType::CPU)
	{
		UE_LOG(LogTemp,Warning,TEXT("CPU Player detected!"));
		UUCIController* UCIController = NewObject<UUCIController>();
		UCIController->Initialize(ChessboardController->GetChessboard(),this,ChessData);
		UCIController->SetCPUDifficulty(GameMode->GetRoundSettings().CPUDifficulty);
		GameRoundController->SetUCIController(UCIController);
	}
	GameRoundController->ConnectToTurnEndedEvent(*GameMode);
	GameRoundController->InitializeRound(GameMode->GetRoundSettings());
	GameRoundController->RoundStarted();
}

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	CreateChessboardSceneUtilities();
	GameMode = ChessboardSceneUtilities->GetBoardWorld()->GetAuthGameMode<AChessGameMode>();
	GameState = ChessboardSceneUtilities->GetBoardWorld()->GetGameState<AChessGameState>();
	CreateChessHighlighter();
	CreateChessboardController();
	GameMode->SetMovementProvider(ChessboardController->GetChessboardMovementRuleProvider());
	GameMode->GameStartedEvent.AddDynamic(this,&AChessController::SetupGameRoundController);
	UE_LOG(LogTemp,Warning,TEXT("Waiting for game start!"));
}

void AChessController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(GameRoundController)
	{
		GameRoundController->Tick(DeltaSeconds);
	}
}

void AChessController::CreateChessboardSceneUtilities()
{
	ChessboardSceneUtilities = NewObject<UChessSceneUtilities>();
	ChessboardSceneUtilities->Initialize(ChessData, ChessBoardOrigin);
}

void AChessController::CreateChessHighlighter()
{
	Highlighter = NewObject<UChessHighlighter>();
	auto HighlightClickedCallback = [this](const FMove Move)
	{
		this->MoveSelected(Move);
	};
	Highlighter->Initialize(ChessData->GetBoardHighlightActor(), ChessboardSceneUtilities, HighlightClickedCallback);
}

void AChessController::CreateChessboardController()
{
	ChessboardController = NewObject<UChessboardController>();
	AChessGameState* ChessGameState = ChessboardSceneUtilities->GetBoardWorld()->GetGameState<AChessGameState>();
	if (!ChessGameState->GetChessboard())
	{
		ChessGameState->CreateChessboard();
	}
	auto FigureClickedCallback = [this](const AChessFigure* Figure)
	{
		this->ChessFigureSelected(Figure);
	};

	ChessboardController->Initialize(ChessboardSceneUtilities, ChessData, FigureClickedCallback);
	ChessboardController->SetupPiecesCallbacks(GameMode);
}

void AChessController::ChessFigureSelected(const AChessFigure* ChessFigure) const
{
	if(ChessFigure->GetColor() != GameState->GetCurrentPlayer())
	{
		return;
	}
	TArray<FMove> Moves = ChessFigure->GetSourcePiece()->GetAvailableMoves();
	Highlighter->CreateHighlights(Moves);
}

void AChessController::MoveSelected(const FMove Move)
{
	ExecutePlayerMove(Move);
}

void AChessController::ExecutePlayerMove(const FMove Move)
{
	UChessPiece* SourcePiece = Cast<UChessPiece>(Move.SourcePiece);
	UChessPiece* TargetPiece = Cast<UChessPiece>(Move.TargetObject);
	const FIntPoint TargetPosition = Move.TargetPosition;
	ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (Move.MoveType != EMoveType::Standard)
	{
		ChessboardController->HandleSpecialMoveType(Move);
	}
	if(TargetPiece)
	{
		OnPieceCaptured.Broadcast(TargetPiece->GetColor(),TargetPiece->GetFigureType());
	}
	GameMode->EndTurn();
}

void AChessController::ResetChessGame() const
{
	ChessboardController->ResetChessboard();
	Highlighter->ClearHighlights();
	GameState->SetCurrentPlayer(EColor::White);
}


APawn* AChessController::GetPlayerPawnByColor(const EColor PlayerColor) const
{
	if(PlayerColor==EColor::White)
	{
		return FirstPlayerPawn;
	}
	if(PlayerColor==EColor::Black)
	{
		return SecondPlayerPawn;
	}
	throw "Invalid Player Color provided! Returning null.";
}


APawn* AChessController::GetPlayerPawn(const int Index) const
{
	if(Index==0)
	{
		return FirstPlayerPawn;
	}
	if(Index==1)
	{
		return SecondPlayerPawn;
	}
	throw "Invalid Player Index provided! Returning null.";
}
