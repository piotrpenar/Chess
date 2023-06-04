#pragma once

UENUM(BlueprintType)
enum class EPlayer
{
	None = -1 UMETA(DisplayName = "None"),
	First = 0 UMETA(DisplayName = "First"),
	Second = 1 UMETA(DisplayName = "Second"),
};
