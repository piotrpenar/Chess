#include "AChessFigure.h"

void AChessFigure::HandleFigureClick()
{
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

TScriptInterface<IChessPieceMovement> AChessFigure::GetSourcePiece() const
{
	return SourcePiece;
}

void AChessFigure::SetClickCallback(const TFunction<void(AChessFigure*)> Function)
{
	CallbackFunction = Function;
}
