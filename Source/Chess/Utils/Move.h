#pragma once
#include "Chess/Enums/MoveType.h"
#include "Move.generated.h"

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

	FMove(): SourcePiece(nullptr), TargetPosition(), TargetObject(nullptr), MoveType()
	{
	}

	FMove(UObject* Source, const FIntPoint Position, UObject* Object, EMoveType Type = EMoveType::Standard)
	{
		SourcePiece = Source;
		TargetPosition = Position;
		TargetObject = Object;
		MoveType = Type;
	}
};
