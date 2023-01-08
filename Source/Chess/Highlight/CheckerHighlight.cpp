#include "CheckerHighlight.h"

ACheckerHighlight::ACheckerHighlight()
{
}

void ACheckerHighlight::NotifyHighlighterOnClick()
{
	Highlighter->HighlightSelected(this);
}
