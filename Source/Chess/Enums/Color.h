#pragma once

UENUM(BlueprintType)
enum class EColor : uint8
{
	White = 0 UMETA(DisplayName = "White"),
	Black = 1 UMETA(DisplayName = "Black"),
	Unspecified = 255 UMETA(DisplayName = "Unspecified"),
};
