// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess/ChessPieces/AChessFigure.h"
#include "Chess/Utils/EFigureType.h"
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
	TMap<EFigureType, UStaticMesh*> FigureToMesh;
public:
	UStaticMesh* GetMeshForType(EFigureType Figure) const;
	TSubclassOf<AChessFigure> GetChessFigureActor() const;
};
