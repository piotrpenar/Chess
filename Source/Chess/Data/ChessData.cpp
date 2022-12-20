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

TSubclassOf<ACheckerHighlight> UChessData::GetCheckerHighlightActor() const
{
	return ChessHighlightActor;
}

bool UChessData::IsValidPosition(const FVector2D& Vector2) const
{
	//TODO: Rename to IsValidBoardPosition
	return Vector2.X >= 0 && Vector2.X < BoardSize && Vector2.Y >= 0 && Vector2.Y < BoardSize;
}

