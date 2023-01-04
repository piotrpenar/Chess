#pragma once
#include "FMove.generated.h"

USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()
	
	UPROPERTY()
	FIntPoint TargetPosition;
	UPROPERTY()
	UObject* TargetObject;

	FMove(): TargetObject(nullptr)
	{
	}

	FMove(const FIntPoint Position,UObject* Object)
	{
		TargetPosition = Position;
		TargetObject = Object;
	}
};
