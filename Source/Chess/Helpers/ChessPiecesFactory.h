// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "UObject/Object.h"
#include "ChessPiecesFactory.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessPiecesFactory : public UObject
{
	GENERATED_BODY()

public:
	static UChessPiece* GenerateChessPiece (const EFigureType FigureType,UObject* Initializer);
	static UChessPiece* CloneChessPiece(UChessPiece* Original, UObject* Initializer);
};
