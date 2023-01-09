#pragma once

#include "CoreMinimal.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EColor.h"
#include "UObject/Object.h"
#include "ChessboardTransformUtilities.generated.h"

UCLASS()
class CHESS_API UChessboardTransformUtilities final: public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	AActor* ChessBoardOrigin;
	
public:
	void Initialize(UChessData* ChessDataReference,AActor* ChessBoardOriginReference);
	FTransform GenerateChessPieceTransform(FIntPoint Position, EColor Color) const;
	FTransform GetChessBoardTransform() const;
	FTransform BoardToWorldTransform(FIntPoint Position) const;
};
