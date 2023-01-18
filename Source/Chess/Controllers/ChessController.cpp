#include "ChessController.h"

#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Highlight/ChessHighlighter.h"

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	CreateChessboardSceneUtilities();
	GameMode = ChessboardSceneUtilities->GetBoardWorld()->GetAuthGameMode<AChessGameMode>();
	GameState = ChessboardSceneUtilities->GetBoardWorld()->GetGameState<AChessGameState>();
	CreateChessHighlighter();
	CreateChessboardController();
	GameMode->SetMovementProvider(ChessboardController->GetChessboardMovementRuleProvider());
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
	auto FigureClickedCallback = [this](const AChessFigure* Figure)
	{
		this->ChessFigureSelected(Figure);
	};

	AChessGameState* ChessGameState = ChessboardSceneUtilities->GetBoardWorld()->GetGameState<AChessGameState>();
	if (!ChessGameState->GetChessboard())
	{
		ChessGameState->CreateChessboard();
	}
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

void AChessController::MoveSelected(const FMove Move) const
{
	ExecutePlayerMove(Move);
}

void AChessController::ExecutePlayerMove(const FMove Move) const
{
	UChessPiece* SourcePiece = Cast<UChessPiece>(Move.SourcePiece);
	const FIntPoint TargetPosition = Move.TargetPosition;
	ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (Move.MoveType != EMoveType::Standard)
	{
		ChessboardController->HandleSpecialMoveType(Move);
	}
	GameMode->EndTurn();
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
