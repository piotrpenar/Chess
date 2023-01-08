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

bool UChessData::IsValidBoardPosition(const FIntPoint& Position) const
{
	return Position.X >= 0 && Position.X < BoardSize && Position.Y >= 0 && Position.Y < BoardSize;
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

