﻿#pragma once
#include "CoreMinimal.h"
#include "Chess/Highlight/BoardHighlight.h"
#include "Chess/Utils/FMove.h"
#include "ChessMovesHighlighter.generated.h"

UINTERFACE()
class UChessMovesHighlighter : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IChessMovesHighlighter
{
	GENERATED_BODY()

public:
	virtual void Initialize(TSubclassOf<ABoardHighlight> BoardHighlightSourceActor);
	virtual void CreateHighlights(TArray<FMove> Moves);
	virtual void SetSelectedFigure(AActor* SourceFigure);
	virtual void HighlightSelected(ABoardHighlight* CheckerHighlight);
};
