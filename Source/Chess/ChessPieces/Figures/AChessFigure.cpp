#include "AChessFigure.h"
#include "Chess/Utils/FMove.h"

void AChessFigure::GetAvailableMoves()
{
	const TArray<FMove> Moves = TArray<FMove>(SourcePiece->GetAvailableMoves());
	Highlighter->CreateHighlight(Moves);
	UE_LOG(LogTemp, Log, TEXT("Avaliable Moves: %d"), Moves.Num())
}
