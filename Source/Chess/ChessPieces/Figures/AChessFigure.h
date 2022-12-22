#pragma once
#include "Chess/Interfaces/BoardHighlighter.h"
#include "Chess/Interfaces/MovesProvider.h"
#include "AChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FVector2D BoardPosition;
public:

	UFUNCTION(BlueprintCallable)
	void HandleFigureClick();
	
	IMovesProvider* SourcePiece;
	IBoardHighlighter* Highlighter;
	void SetBoardPosition(FVector2D NewBoardPosition);
	FVector2D GetBoardPosition() const;
};