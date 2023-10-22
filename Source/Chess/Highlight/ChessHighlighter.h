#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/ChessSceneUtilities.h"
#include "Chess/ChessPieces/Figures/ChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"
#include "Chess/Interfaces/ChessMovesHighlighter.h"
#include "Chess/Utils/Move.h"
#include "ChessHighlighter.generated.h"

UCLASS()
class CHESS_API UChessHighlighter final : public UObject, public IChessMovesHighlighter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<ABoardHighlight*> CurrentHighlights;
	UPROPERTY()
	TArray<AChessFigure*> HighlightedFigures;
	UPROPERTY()
	AChessFigure* CurrentSelectedFigure;
	UPROPERTY()
	TSubclassOf<ABoardHighlight> BoardHighlightActor;
	UPROPERTY()
	UChessSceneUtilities* ChessboardTransformUtilities;

	TFunction<void(FMove)> HighlightClickCallback;
	

public:
	virtual void ClearHighlights() override;
	virtual void Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessSceneUtilities* ChessSceneUtilitiesReference,
	                        TFunction<void(FMove)> HighlightClickCallbackReference) override;
	virtual void CreateHighlights(TArray<FMove>& Moves) override;
	virtual void SetSelectedFigure(AActor* SelectedFigureActor) override;
	virtual void HighlightSelected(ABoardHighlight* CheckerHighlight) override;
	ABoardHighlight* GetHighlightFromMove(const FMove& Move);
	void ClearPiecesHighlights();
	virtual void CreatePiecesHighlights(TArray<FMove>& Moves) override;
};
