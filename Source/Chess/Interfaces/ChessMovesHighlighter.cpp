#include "ChessMovesHighlighter.h"

void IChessMovesHighlighter::Initialize(TSubclassOf<ABoardHighlight> BoardHighlightSourceActor)
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
