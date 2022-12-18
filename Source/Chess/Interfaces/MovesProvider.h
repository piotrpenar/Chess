﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "UObject/Interface.h"
#include "MovesProvider.generated.h"

UINTERFACE()
class UMovesProvider : public UInterface
{
	GENERATED_BODY()
};

class CHESS_API IMovesProvider
{
	GENERATED_BODY()

public:
	virtual TArray<FMove> GetAvailableMoves();
};