// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Highlight/CheckerHighlight.h"
#include "Chess/Utils/EFigure.h"
#include "ChessData.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UChessData final : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AChessFigure> ChessFigureActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACheckerHighlight> ChessHighlightActor;
	UPROPERTY(EditAnywhere)
	TMap<EFigure, UStaticMesh*> FigureToMesh;
	UPROPERTY(EditAnywhere)
	float BoardCheckerSize = 100;
	UPROPERTY(EditAnywhere)
	int BoardSize = 8;
	UPROPERTY(EditAnywhere)
	float BoardOffset = 1;
	
public:
	UStaticMesh* GetMeshForType(EFigure Figure) const;
	TSubclassOf<AChessFigure> GetChessFigureActor() const;
	TSubclassOf<ACheckerHighlight> GetCheckerHighlightActor() const;
	bool IsValidBoardPosition(const FIntPoint& Position) const;
	float GetBoardCheckerSize();
	float GetBoardSize();
	float GetBoardOffset();
};
