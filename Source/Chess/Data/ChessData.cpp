#include "ChessData.h"

float UChessData::GetBoardCheckerSize() const
{
	return BoardCheckerSize;
}

float UChessData::GetBoardSize() const
{
	return BoardSize;
}

float UChessData::GetBoardOffset() const
{
	return BoardOffset;
}

TArray<EFigure> UChessData::GetMen() const
{
	return Men;
}

TArray<EFigure> UChessData::GetPawns() const
{
	return Pawns;
}

TMap<FString, int> UChessData::GetCPUDifficulties() const
{
	return CPUDifficulties;
}

TMap<FString, int> UChessData::GetAvailableGameLengths() const
{
	return AvailableGameLengths;
}

FString UChessData::GetStockfishPath()
{
	return StockfishPath;
}

UStaticMesh* UChessData::GetMeshForType(const EFigure Figure) const
{
	if (!FigureToMesh.Contains(Figure))
	{
		UE_LOG(LogTemp, Error, TEXT("ChessData does not contain requested Mesh"));
		return nullptr;
	}
	return FigureToMesh[Figure].Mesh;
}

UMaterialInstance* UChessData::GetMaterialForType(const EFigure Figure, const EColor Color) const
{
	if (!FigureToMesh.Contains(Figure))
	{
		UE_LOG(LogTemp, Error, TEXT("ChessData does not contain requested Materials"));
		return nullptr;
	}
	if (Color == EColor::White)
	{
		return FigureToMesh[Figure].WhiteMaterial;
	}

	return FigureToMesh[Figure].BlackMaterial;
}

TSubclassOf<AChessFigure> UChessData::GetChessFigureActor() const
{
	return ChessFigureActor;
}

TSubclassOf<ABoardHighlight> UChessData::GetBoardHighlightActor() const
{
	return ChessHighlightActor;
}