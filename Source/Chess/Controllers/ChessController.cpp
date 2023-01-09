#include "ChessController.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Highlight/ChessHighlighter.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	Highlighter = NewObject<UChessHighlighter>();
	Highlighter->Initialize(ChessData->GetCheckerHighlightActor());
	ChessboardController = NewObject<UChessboardController>();
	ChessboardController->Initialize(ChessData, ChessBoardOrigin, this);
}

void AChessController::ChessFigureSelected(const AChessFigure* ChessFigure) const
{
	UE_LOG(LogTemp, Log, TEXT("Callback called %d!"), ChessFigure->GetBoardPosition().X)
}

void AChessController::HighlightSelected(const ABoardHighlight* BoardHighlight) const
{
	ExecutePlayerMove(BoardHighlight->GetSourceMove());
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

