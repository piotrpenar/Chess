#pragma once

#include "CoreMinimal.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/Color.h"
#include "UObject/Object.h"
#include "ChessSceneUtilities.generated.h"

UCLASS()
class CHESS_API UChessSceneUtilities final : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	AActor* ChessBoardOrigin;

public:
	void Initialize(UChessData* ChessDataReference, AActor* ChessBoardOriginReference);
	FTransform GenerateChessPieceTransform(FIntPoint Position, EColor Color) const;
	FTransform GetChessBoardTransform() const;
	FTransform BoardToWorldTransform(FIntPoint Position) const;
	UWorld* GetBoardWorld() const;
};
