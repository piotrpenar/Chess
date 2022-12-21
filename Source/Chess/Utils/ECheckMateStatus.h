#pragma once

UENUM()
enum class ECheckMateStatus : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Mate = 1 UMETA(DisplayName = "Mate"),
	Checkmate = 2 UMETA(DisplayName = "Checkmate"),
};
