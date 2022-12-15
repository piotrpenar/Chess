// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessData.h"

UStaticMesh* UChessData::GetMeshForType(EFigureType Figure) const
{
	return FigureToMesh[Figure];
}
