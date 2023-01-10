#pragma once
#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "BoardHighlight.generated.h"

UCLASS()
class CHESS_API ABoardHighlight final : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AChessFigure* SourceFigure;
	UPROPERTY()
	FIntPoint Position;
	UPROPERTY()
	FMove Move;

	TFunction<void(ABoardHighlight*)> HighlightClickedCallback;

public:
	ABoardHighlight();

	UFUNCTION(BlueprintCallable)
	void BroadcastHighlightOnClick();

	void Initialize(const FMove SourceMove, AChessFigure* ChessFigure, TFunction<void(ABoardHighlight*)> HighlightClickedCallbackReference);
	AChessFigure* GetSourceFigure() const;
	FMove GetSourceMove() const;
};
