#pragma once

UENUM(BlueprintType)
enum class EPowerupType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Chicken = 1 UMETA(DisplayName = "Chicken"),
	Speed = 2 UMETA(DisplayName = "Speedup"),
	Shield = 3 UMETA(DisplayName = "Shield"),
};
