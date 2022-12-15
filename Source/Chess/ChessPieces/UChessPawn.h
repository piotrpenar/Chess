#pragma once
#include "UChessPiece.h"
#include "UChessPawn.generated.h"

UCLASS()
class UChessPawn final : public UChessPiece
{
	GENERATED_BODY()
public:
	int someData;
	
};
