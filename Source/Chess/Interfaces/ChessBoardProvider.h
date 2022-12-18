// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChessBoardProvider.generated.h"

UINTERFACE()
class UChessBoardProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IChessBoardProvider
{
	GENERATED_BODY()
public:
	virtual UObject* GetPieceAtPosition(FVector2D BoardPosition);
};
