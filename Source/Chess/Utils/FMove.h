#pragma once
#include "Chess/ChessPieces/ChessPiece.h"
#include "FMove.generated.h"

USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FVector2D TargetPosition;
	UPROPERTY()
	UChessPiece* TargetObject;

	FMove(FVector2D Position,UChessPiece* Object)
	{
		TargetPosition = Position;
		TargetObject = Object;
	}
};
