// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "GameFramework/Actor.h"
#include "CheckerHighlight.generated.h"

UCLASS()
class CHESS_API ACheckerHighlight final : public AActor
{
	GENERATED_BODY()

public:
	ACheckerHighlight();

	//TODO: Add getters / setters
	UPROPERTY()
	AChessFigure* SourceFigure;
	IBoardHighlighter* Highlighter;
	FIntPoint Position;
	
	UFUNCTION(BlueprintCallable)
	void NotifyHighlighterOnClick();
};
