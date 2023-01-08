// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessData.h"

#include "Chess/Utils/EColor.h"

UStaticMesh* UChessData::GetMeshForType(const EFigure Figure) const
{
	if(!FigureToMesh.Contains(Figure))
	{
		UE_LOG(LogTemp, Error, TEXT("ChessData does not contain requested Mesh"));
		return nullptr;
	}
	return FigureToMesh[Figure].Mesh;
}

UMaterialInstance* UChessData::GetMaterialForType(const EFigure Figure,const EColor Color) const
{
	if(!FigureToMesh.Contains(Figure))
	{
		UE_LOG(LogTemp, Error, TEXT("ChessData does not contain requested Materials"));
		return nullptr;
	}
	if(Color == EColor::White)
	{
		return FigureToMesh[Figure].WhiteMaterial;
	}

	return FigureToMesh[Figure].BlackMaterial;
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

