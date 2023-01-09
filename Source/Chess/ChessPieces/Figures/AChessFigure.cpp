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
	ChessFigureClicked.ExecuteIfBound(this);
}

AChessFigure::FChessFigureClicked AChessFigure::OnChessFigureClicked()
{
	return ChessFigureClicked;
}

void AChessFigure::SetBoardPosition(FIntPoint NewBoardPosition)
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
