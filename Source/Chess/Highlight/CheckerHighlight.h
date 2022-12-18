// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "GameFramework/Actor.h"
#include "CheckerHighlight.generated.h"

UCLASS()
class CHESS_API ACheckerHighlight : public AActor
{
	GENERATED_BODY()

public:
	ACheckerHighlight();
	UPROPERTY()
	AChessFigure* SourceFigure;
	IBoardHighlighter* Highlighter;
	FVector2D Position;
	UFUNCTION(BlueprintCallable)
	void NotifyHighlighterOnClick();
};
