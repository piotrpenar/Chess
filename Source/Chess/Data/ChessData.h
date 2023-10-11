#pragma once
#include "CoreMinimal.h"
#include "Chess/ChessPieces/Figures/ChessFigure.h"
#include "Chess/Enums/Color.h"
#include "Chess/Enums/Figure.h"
#include "Chess/Highlight/BoardHighlight.h"
#include "Chess/Utils/CPUDifficulty.h"
#include "ChessData.generated.h"

USTRUCT()
struct FMeshMaterialData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,meta = (IgnoreForMemberInitializationTest))
	UStaticMesh* Mesh = nullptr;
	UPROPERTY(EditAnywhere,meta = (IgnoreForMemberInitializationTest))
	UMaterialInstance* WhiteMaterial = nullptr;
	UPROPERTY(EditAnywhere,meta = (IgnoreForMemberInitializationTest))
	UMaterialInstance* BlackMaterial = nullptr;
};

UCLASS(BlueprintType)
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
	UPROPERTY(EditAnywhere)
	TMap<FString,int> CPUDifficulties;
	UPROPERTY(EditAnywhere)
	TMap<FString,int> AvailableGameLengths;

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
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TMap<FString,int> GetCPUDifficulties() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
	TMap<FString,int> GetAvailableGameLengths() const;

	bool IsValidBoardPosition(const FIntPoint& Position) const;
};
