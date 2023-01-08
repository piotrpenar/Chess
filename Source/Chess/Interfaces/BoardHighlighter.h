

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "UObject/Interface.h"
#include "BoardHighlighter.generated.h"

UINTERFACE()
class UBoardHighlighter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IBoardHighlighter
{
	GENERATED_BODY()

public:
	virtual void CreateHighlights(TArray<FMove> Moves);
	virtual void SetSelectedFigure(AActor* SourceFigure);
	virtual void HighlightSelected(AActor* Source);
};
