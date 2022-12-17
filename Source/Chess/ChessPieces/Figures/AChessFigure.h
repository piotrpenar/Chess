#pragma once
#include "Chess/ChessPieces/Interfaces/MovesProvider.h"
#include "AChessFigure.generated.h"

UCLASS()
class AChessFigure final : public AActor
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void GetAvailableMoves();
	
	IMovesProvider* SourcePiece;
	
};