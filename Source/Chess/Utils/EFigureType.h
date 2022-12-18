#pragma once

UENUM()
enum class EFigureType : uint8
{
	Pawn = 0 UMETA(DisplayName = "Pawn"),
	Rook = 1 UMETA(DisplayName = "Rook"),
	Knight = 2 UMETA(DisplayName = "Knight"),
	Bishop = 3 UMETA(DisplayName = "Bishop"),
	Queen = 4 UMETA(DisplayName = "Queen"),
	King = 5 UMETA(DisplayName = "King"),
	Invalid = 255 UMETA(DisplayName = "Invalid"),
};
