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

ABoardHighlight::FHighlightClicked ABoardHighlight::OnHighlightClicked()
{
	return HighlightClicked;
}

void ABoardHighlight::Initialize(const FMove& SourceMove, AChessFigure* ChessFigure)
{
	Position = SourceMove.TargetPosition;
	SourceFigure = ChessFigure;
	Move = SourceMove;
}

void ABoardHighlight::BroadcastHighlightOnClick()
{
	HighlightClicked.ExecuteIfBound(this);
}
