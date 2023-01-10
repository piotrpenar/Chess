#include "ChessController.h"

#include "ChessGameMode.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Highlight/ChessHighlighter.h"

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	CreateChessboardSceneUtilities();
	GameMode = ChessboardSceneUtilities->GetBoardWorld()->GetAuthGameMode<AChessGameMode>();
	CreateChessHighlighter();
	CreateChessboardController();
	GameMode->SetMovementProvider(ChessboardController->GetChessboardMovementRuleProvider());
}

void AChessController::CreateChessboardSceneUtilities()
{
	ChessboardSceneUtilities = NewObject<UChessSceneUtilities>();
	ChessboardSceneUtilities->Initialize(ChessData,ChessBoardOrigin);
}

void AChessController::CreateChessHighlighter()
{
	Highlighter = NewObject<UChessHighlighter>();
	auto HighlightClickedCallback = [this](const FMove* Move)
	{
		this->MoveSelected(Move);
	};
	Highlighter->Initialize(ChessData->GetBoardHighlightActor(), ChessboardSceneUtilities,HighlightClickedCallback);
}

void AChessController::CreateChessboardController()
{
	ChessboardController = NewObject<UChessboardController>();
	auto FigureClickedCallback = [this](const AChessFigure* Figure)
	{
		this->ChessFigureSelected(Figure);
	};

	AChessGameState* ChessGameState = ChessboardSceneUtilities->GetBoardWorld()->GetGameState<AChessGameState>();
	if(!ChessGameState->GetChessboard())
	{
		ChessGameState->CreateChessboard();
	}
	ChessboardController->Initialize(ChessboardSceneUtilities, ChessData,FigureClickedCallback);
	ChessboardController->SetupPiecesCallbacks(GameMode);
}

void AChessController::ChessFigureSelected(const AChessFigure* ChessFigure) const
{
	UE_LOG(LogTemp, Log, TEXT("Callback called %d!"), ChessFigure->GetBoardPosition().X)
	Highlighter->CreateHighlights(ChessFigure->GetSourcePiece()->GetAvailableMoves());
}

void AChessController::MoveSelected(const FMove* Move) const
{
	UE_LOG(LogTemp, Log, TEXT("Callback called 123 %s!"), *FString(Move->TargetPosition.ToString()))
	ExecutePlayerMove(*Move);
}

void AChessController::ExecutePlayerMove(const FMove Move) const
{
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(Move.SourcePiece);
	const FIntPoint TargetPosition = Move.TargetPosition;
	ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (Move.MoveType != EMoveType::Standard)
	{
		ChessboardController->HandleSpecialMoveType(Move);
	}
	GameMode->EndTurn();
}

