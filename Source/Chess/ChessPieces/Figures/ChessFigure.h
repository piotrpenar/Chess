#pragma once
#include "Chess/Enums/Color.h"
#include "Chess/Interfaces/ChessPieceMovement.h"
#include "ChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FIntPoint BoardPosition;
	
	UPROPERTY()
	EColor FigureColor;

	UPROPERTY()
	TScriptInterface<IChessPieceMovement> SourcePiece;

	TFunction<void(AChessFigure*)> CallbackFunction;

	UFUNCTION(BlueprintCallable)
	void HandleFigureClick();
	
	void BroadcastChessFigureOnClick();
	
public:
	void SetBoardPosition(FIntPoint NewBoardPosition);
	FIntPoint GetBoardPosition() const;
	void SetSourcePiece(TScriptInterface<IChessPieceMovement> ChessPiece);
	TScriptInterface<IChessPieceMovement> GetSourcePiece() const;
	void SetClickCallback(TFunction<void(AChessFigure*)> FigureClickedCallback);
	EColor GetColor() const;
	void SetColor(EColor Color);
};
