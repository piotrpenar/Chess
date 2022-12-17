#include "AChessFigure.h"
#include "Chess/Utils/FMove.h"

void AChessFigure::GetAvailableMoves()
{
	FMove test;
	TArray<FMove> Moves = TArray<FMove>(SourcePiece->GetAvailableMoves());
	UE_LOG(LogTemp, Log, TEXT("HALO STRYTA SIE PALI"))
	UE_LOG(LogTemp, Log, TEXT("LICZBA RUCHÓW: %d"), Moves.Num())
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}
