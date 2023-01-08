#pragma once
#include "EMoveType.h"
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
	UPROPERTY()
	EMoveType MoveType;

	FMove(): TargetObject(nullptr)
	{
	}

	FMove(UObject* Source,const FIntPoint Position,UObject* Object,EMoveType Type = EMoveType::Standard)
	{
		SourcePiece = Source;
		TargetPosition = Position;
		TargetObject = Object;
		MoveType = Type;
	}
};
