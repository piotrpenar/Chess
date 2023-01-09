#include "ChessMovesHighlighter.h"

#include "Chess/Chessboard/ChessboardTransformUtilities.h"

void IChessMovesHighlighter::Initialize(TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessboardTransformUtilities* ChessboardTransformUtilities)
{
}

void IChessMovesHighlighter::CreateHighlights(TArray<FMove> Moves)
{
}

void IChessMovesHighlighter::SetSelectedFigure(AActor* SourceFigure)
{
}

void IChessMovesHighlighter::HighlightSelected(ABoardHighlight* CheckerHighlight)
{
}
