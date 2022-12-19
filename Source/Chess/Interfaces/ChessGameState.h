// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/EColor.h"
#include "UObject/Interface.h"
#include "ChessGameState.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UChessGameState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IChessGameState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EColor GetCurrentPlayer() ;
	virtual void EndTurn();
};
