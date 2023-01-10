#pragma once
#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "ChessPiecesFactory.generated.h"

UCLASS()
class CHESS_API UChessPiecesFactory final : public UObject
{
	GENERATED_BODY()

public:
	static UChessPiece* GenerateChessPiece(const EFigure FigureType, UObject* Initializer);
	static UChessPiece* CloneChessPiece(UChessPiece* Original, UObject* Initializer);
};
