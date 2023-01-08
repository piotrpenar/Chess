#pragma once
#include "FMove.generated.h"

USTRUCT(BlueprintType)
struct FMove
{
	GENERATED_BODY()
	
	UPROPERTY()
	UObject* SourcePiece;
	UPROPERTY()
	FIntPoint TargetPosition;
	UPROPERTY()
	UObject* TargetObject;

	FMove(): TargetObject(nullptr)
	{
	}

	FMove(UObject* Source,const FIntPoint Position,UObject* Object)
	{
		SourcePiece = Source;
		TargetPosition = Position;
		TargetObject = Object;
	}
};
