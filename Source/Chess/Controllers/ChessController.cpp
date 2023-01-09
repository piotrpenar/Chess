#include "ChessController.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Highlight/ChessHighlighter.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	ChessboardTransformUtilities = NewObject<UChessSceneUtilities>();
	ChessboardTransformUtilities->Initialize(ChessData,ChessBoardOrigin);
	Highlighter = NewObject<UChessHighlighter>();
	auto HighlightClickedCallback = [this](const FMove* Highlight)
	{
		this->HighlightSelected(Highlight);
	};
	Highlighter->Initialize(ChessData->GetBoardHighlightActor(), ChessboardTransformUtilities,HighlightClickedCallback);
	ChessboardController = NewObject<UChessboardController>();
	auto FigureClickedCallback = [this](const AChessFigure* Figure)
	{
		this->ChessFigureSelected(Figure);
	};
	ChessboardController->Initialize(ChessboardTransformUtilities, ChessData,ChessBoardOrigin, FigureClickedCallback);
}

void AChessController::ChessFigureSelected(const AChessFigure* ChessFigure) const
{
	UE_LOG(LogTemp, Log, TEXT("Callback called %d!"), ChessFigure->GetBoardPosition().X)
	Highlighter->CreateHighlights(ChessFigure->GetSourcePiece()->GetAvailableMoves());
}

void AChessController::HighlightSelected(const FMove* Move) const
{
	UE_LOG(LogTemp, Log, TEXT("Callback called %s!"), *FString(Move->TargetPosition.ToString()))
	ExecutePlayerMove(*Move);
}

void AChessController::ExecutePlayerMove(const FMove Move) const
{
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(Move.SourcePiece);
	UChessPiece* TargetPiece = static_cast<UChessPiece*>(Move.TargetObject);
	const FIntPoint TargetPosition = Move.TargetPosition;
	ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (Move.MoveType != EMoveType::Standard)
	{
		ChessboardController->HandleSpecialMoveType(Move);
	}
	//TODO: Implement this
	//ChessGameState->EndTurn();
}

