#pragma once
#include "Chess/Interfaces/BoardHighlighter.h"
#include "Chess/Interfaces/MovesProvider.h"
#include "AChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FIntPoint BoardPosition;
public:

	UFUNCTION(BlueprintCallable)
	void HandleFigureClick();
	
	IMovesProvider* SourcePiece;
	IBoardHighlighter* Highlighter;
	void SetBoardPosition(FIntPoint NewBoardPosition);
	FIntPoint GetBoardPosition() const;
};