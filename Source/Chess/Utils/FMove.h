#pragma once
#include "FMove.generated.h"

USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FVector2D TargetPosition;
	UPROPERTY()
	UObject* TargetObject;

	FMove()
	{
	}
	
	FMove(FVector2D Position,UObject* Object)
	{
		TargetPosition = Position;
		TargetObject = Object;
	}
};
