// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessData.h"

UStaticMesh* UChessData::GetMeshForType(const EFigureType Figure) const
{
	return FigureToMesh[Figure];
}

TSubclassOf<AChessFigure> UChessData::GetChessFigureActor() const
{
	return ChessFigureActor;
}
