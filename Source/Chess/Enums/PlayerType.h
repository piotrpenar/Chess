#pragma once

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	Human = 0 UMETA(DisplayName = "Human"),
	CPU = 1 UMETA(DisplayName = "CPU"),
	Unknown = 255 UMETA(DisplayName = "Unknown"),
};
