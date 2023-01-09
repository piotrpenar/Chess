#pragma once
#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Highlight/BoardHighlight.h"
#include "ChessData.generated.h"

USTRUCT()
struct FMeshMaterialData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* WhiteMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* BlackMaterial;
};

UCLASS()
class CHESS_API UChessData final : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AChessFigure> ChessFigureActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABoardHighlight> ChessHighlightActor;
	UPROPERTY(EditAnywhere)
	TMap<EFigure, FMeshMaterialData> FigureToMesh;
	UPROPERTY(EditAnywhere)
	float BoardCheckerSize = 100;
	UPROPERTY(EditAnywhere)
	int BoardSize = 8;
	UPROPERTY(EditAnywhere)
	float BoardOffset = 1;
	
	const TArray<EFigure> Pawns = {
		EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn, EFigure::Pawn,
		EFigure::Pawn, EFigure::Pawn
	};
	const TArray<EFigure> Men = {
		EFigure::Rook, EFigure::Knight, EFigure::Bishop, EFigure::King, EFigure::Queen, EFigure::Bishop,
		EFigure::Knight, EFigure::Rook
	};

public:
	UStaticMesh* GetMeshForType(EFigure Figure) const;
	UMaterialInstance* GetMaterialForType(EFigure Figure, EColor Color) const;
	TSubclassOf<AChessFigure> GetChessFigureActor() const;
	TSubclassOf<ABoardHighlight> GetBoardHighlightActor() const;
	float GetBoardCheckerSize() const;
	float GetBoardSize() const;
	float GetBoardOffset() const;
	TArray<EFigure> GetMen() const;
	TArray<EFigure> GetPawns() const;
	
	bool IsValidBoardPosition(const FIntPoint& Position) const;
};
