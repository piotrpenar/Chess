#include "ChessMovesHighlighter.h"

#include "Chess/Chessboard/ChessSceneUtilities.h"

void IChessMovesHighlighter::Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessSceneUtilities* ChessSceneUtilitiesReference, TFunction<void(FMove*)> HighlightClickCallbackReference)
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
