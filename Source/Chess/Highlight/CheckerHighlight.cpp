


#include "CheckerHighlight.h"


// Sets default values
ACheckerHighlight::ACheckerHighlight()
{
}

void ACheckerHighlight::NotifyHighlighterOnClick()
{
	Highlighter->HighlightSelected(this);
}
