#pragma once
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Interfaces/ChessPieceMovement.h"
#include "AChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	FIntPoint BoardPosition;
	
	UPROPERTY()
	TScriptInterface<IChessPieceMovement> SourcePiece;

	TFunction<void(AChessFigure*)> CallbackFunction;
	
public:
	UFUNCTION(BlueprintCallable)
	void HandleFigureClick();
	void BroadcastChessFigureOnClick();
	void SetBoardPosition(FIntPoint NewBoardPosition);
	FIntPoint GetBoardPosition() const;
	void SetSourcePiece(TScriptInterface<IChessPieceMovement> ChessPiece);
	void SetClickCallback(TFunction<void(AChessFigure*)> Function);
};
