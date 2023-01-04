// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/Utils/FMove.h"
#include "UObject/Interface.h"
#include "BoardHighlighter.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBoardHighlighter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHESS_API IBoardHighlighter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void CreateHighlights(TArray<FMove> Moves);
	virtual void SetSelectedFigure(AActor* SourceFigure);
	virtual void HighlightSelected(AActor* Source);
};
