#pragma once

UENUM(BlueprintType)
enum class EDebuffs : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Stunned = 1 UMETA(DisplayName = "Stunned"),
	Slowed = 2 UMETA(DisplayName = "Slowed"),
	Morphed = 3 UMETA(DisplayName = "Morphed"),
};

UENUM(BlueprintType)
enum class EBuffs : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Speedup = 1 UMETA(DisplayName = "Speedup"),
	Shielded = 2 UMETA(DisplayName = "Shielded"),
	Invulnerable = 3 UMETA(DisplayName = "Invulnerable"),
	Invisible = 4 UMETA(DisplayName = "Invisible"),
};
