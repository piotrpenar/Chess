#pragma once
#include "Chess/Interfaces/ChessPieceMovement.h"
#include "AChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FIntPoint BoardPosition;
	
	DECLARE_DELEGATE_OneParam(FChessFigureClicked, AChessFigure*)
	FChessFigureClicked ChessFigureClicked;
	
public:
	UFUNCTION(BlueprintCallable)
	void HandleFigureClick();

	UPROPERTY()
	TScriptInterface<IChessPieceMovement> SourcePiece;
	
	void BroadcastChessFigureOnClick();
	FChessFigureClicked OnChessFigureClicked();
	void SetBoardPosition(FIntPoint NewBoardPosition);
	FIntPoint GetBoardPosition() const;
};
