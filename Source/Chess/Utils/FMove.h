#pragma once
#include "FMove.generated.h"

USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector2D TargetPosition;
	UPROPERTY()
	UObject* TargetObject;

	FMove(): TargetObject(nullptr)
	{
	}

	FMove(const FVector2D Position,UObject* Object)
	{
		TargetPosition = Position;
		TargetObject = Object;
	}
};
