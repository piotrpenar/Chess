#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "Chess/Utils/FMove.h"
#include "ChessHighlighter.generated.h"

UCLASS()
class CHESS_API UChessHighlighter final :  public UObject, public IChessMovesHighlighter
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(TSubclassOf<ABoardHighlight> BoardHighlightSourceActor) override;
	virtual void CreateHighlights(TArray<FMove> Moves) override;
	virtual void SetSelectedFigure(AActor* SelectedFigureActor) override;
	virtual void HighlightSelected(ABoardHighlight* CheckerHighlight) override;
	void ClearHighlights();
	
private:
	UPROPERTY()
	TArray<AActor*> CurrentHighlights;
	UPROPERTY()
	AChessFigure* CurrentSelectedFigure;
	UPROPERTY()
	TSubclassOf<ABoardHighlight> BoardHighlightActor;
};
