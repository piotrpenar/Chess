#include "AChessFigure.h"
#include "Chess/Utils/FMove.h"

void AChessFigure::HandleFigureClick()
{
	if (!SourcePiece->CanMoveThisTurn())
	{
		return;
	}
	BroadcastChessFigureOnClick();
}

void AChessFigure::BroadcastChessFigureOnClick()
{
	CallbackFunction(this);
}

void AChessFigure::SetBoardPosition(const FIntPoint NewBoardPosition)
{
	if (!IsValid(this))
	{
		return;
	}
	this->BoardPosition = NewBoardPosition;
}

FIntPoint AChessFigure::GetBoardPosition() const
{
	return BoardPosition;
}

void AChessFigure::SetSourcePiece(const TScriptInterface<IChessPieceMovement> ChessPiece)
{
	SourcePiece = ChessPiece;
}

void AChessFigure::SetClickCallback(const TFunction<void(AChessFigure*)> Function)
{
	CallbackFunction = Function;
}
