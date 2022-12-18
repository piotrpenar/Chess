﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessData.h"

UStaticMesh* UChessData::GetMeshForType(const EFigureType Figure) const
{
	return FigureToMesh[Figure];
}

TSubclassOf<AChessFigure> UChessData::GetChessFigureActor() const
{
	return ChessFigureActor;
}

bool UChessData::IsValidPosition(const FVector2D& Vector2) const
{
	return Vector2.X >= 0 && Vector2.X < BoardSize && Vector2.Y >= 0 && Vector2.Y < BoardSize;
}
