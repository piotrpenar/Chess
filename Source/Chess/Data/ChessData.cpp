// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessData.h"

UStaticMesh* UChessData::GetMeshForType(const EFigure Figure) const
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

bool UChessData::IsValidBoardPosition(const FIntPoint& Vector2) const
{
	return Vector2.X >= 0 && Vector2.X < BoardSize && Vector2.Y >= 0 && Vector2.Y < BoardSize;
}

float UChessData::GetBoardCheckerSize()
{
	return BoardCheckerSize;
}

float UChessData::GetBoardSize()
{
	return BoardSize;
}

float UChessData::GetBoardOffset()
{
	return BoardOffset;
}

