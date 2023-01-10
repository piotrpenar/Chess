#pragma once

UENUM()
enum class ECheckmateStatus : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Check = 1 UMETA(DisplayName = "Check"),
	Checkmate = 2 UMETA(DisplayName = "Checkmate"),
	Stalemate = 3 UMETA(DisplayName = "Stalemate"),
};
