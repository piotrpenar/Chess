// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckerHighlight.h"


// Sets default values
ACheckerHighlight::ACheckerHighlight()
{
}

void ACheckerHighlight::NotifyHighlighterOnClick()
{
	Highlighter->HighlightSelected(this);
}


