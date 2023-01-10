#include "BoardHighlight.h"

ABoardHighlight::ABoardHighlight()
{
}

AChessFigure* ABoardHighlight::GetSourceFigure() const
{
	return SourceFigure;
}

FMove ABoardHighlight::GetSourceMove() const
{
	return Move;
}

void ABoardHighlight::Initialize(const FMove& SourceMove, AChessFigure* ChessFigure,TFunction<void(ABoardHighlight*)> HighlightClickedCallbackReference)
{
	Position = SourceMove.TargetPosition;
	SourceFigure = ChessFigure;
	Move = SourceMove;
	HighlightClickedCallback = HighlightClickedCallbackReference;
}

void ABoardHighlight::BroadcastHighlightOnClick()
{
	HighlightClickedCallback(this);
}
