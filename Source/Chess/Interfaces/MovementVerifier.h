﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Chess/Utils/FMove.h"
#include "MovementVerifier.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMovementVerifier : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IMovementVerifier
{
	GENERATED_BODY()
	
public:
	virtual bool IsValidMove(const FVector2D Position, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromPositions(TArray<FVector2D> Directions, UObject* ChessPiece);
	virtual TArray<FMove> GetValidMovesFromDirections(TArray<FVector2D> Directions, UObject* ChessPiece);
};

