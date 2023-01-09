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
	DECLARE_DELEGATE_OneParam(FHighlightClicked, ABoardHighlight*)
	FHighlightClicked HighlightClicked;
	
public:
	ABoardHighlight();
	void Initialize(const FMove& SourceMove, AChessFigure* ChessFigure);
	UFUNCTION(BlueprintCallable)
	void BroadcastHighlightOnClick();
	AChessFigure* GetSourceFigure() const;
	FMove GetSourceMove() const;
	FHighlightClicked OnHighlightClicked();
	
	
};
