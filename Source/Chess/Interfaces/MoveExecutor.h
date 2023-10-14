// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/Move.h"
#include "UObject/Interface.h"
#include "MoveExecutor.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMoveExecutor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IMoveExecutor
{
	GENERATED_BODY()

public:
	virtual void ExecutePlayerMove(const FMove Move);
};
