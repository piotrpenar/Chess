#include "AChessFigure.h"
#include "Chess/Utils/FMove.h"

void AChessFigure::HandleFigureClick()
{
	if(!SourcePiece->CanMoveThisTurn())
	{
		return;
	}
	const TArray<FMove> Moves = TArray<FMove>(SourcePiece->GetAvailableMoves());
	Highlighter->SetSelectedFigure(this);
	Highlighter->CreateHighlights(Moves);
	UE_LOG(LogTemp, Log, TEXT("Avaliable Moves: %d"), Moves.Num())
}
