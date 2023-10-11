#pragma once

UENUM(BlueprintType)
enum class EChessPlayer : uint8
{
	First = 0 UMETA(DisplayName = "First"),
	Second = 1 UMETA(DisplayName = "Second"),
	None = 255 UMETA(DisplayName = "None"),
};
