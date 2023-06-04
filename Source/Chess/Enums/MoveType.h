#pragma once

UENUM(BlueprintType)
enum class EMoveType : uint8
{
	Standard = 0 UMETA(DisplayName = "Standard"),
	DoubleMove = 1 UMETA(DisplayName = "PawnDoubleMove"),
	EnPassant = 2 UMETA(DisplayName = "PawnEnPassant"),
	Castling = 3 UMETA(DisplayName = "Castling"),
	PawnPromotion = 4 UMETA(DisplayName = "PawnPromotion"),
};
