#pragma once

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	First = 0 UMETA(DisplayName = "First"),
	Second = 1 UMETA(DisplayName = "Second"),
	None = 255 UMETA(DisplayName = "None"),
};
