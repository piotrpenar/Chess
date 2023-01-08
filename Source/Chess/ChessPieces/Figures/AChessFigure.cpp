#include "AChessFigure.h"
#include "Chess/Utils/FMove.h"

void AChessFigure::HandleFigureClick()
{
	if (!SourcePiece->CanMoveThisTurn())
	{
		return;
	}
	const TArray<FMove> Moves = SourcePiece->GetAvailableMoves();
	Highlighter->SetSelectedFigure(this);
	Highlighter->CreateHighlights(Moves);
	UE_LOG(LogTemp, Log, TEXT("Avaliable Moves: %d"), Moves.Num())
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
