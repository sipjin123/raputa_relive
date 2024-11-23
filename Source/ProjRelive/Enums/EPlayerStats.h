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

UENUM(BlueprintType)
enum class EResizeState : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Shrinking = 1 UMETA(DisplayName = "Shrinking"),
	Enlarging = 2 UMETA(DisplayName = "Enlarging")
};

UENUM(BlueprintType)
enum class EActorType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Chicken = 1 UMETA(DisplayName = "Chicken"),
	TreasureChest = 2 UMETA(DisplayName = "TreasureChest"),
	Landmine = 3 UMETA(DisplayName = "Landmine"),
	PowerupChest = 4 UMETA(DisplayName = "PowerupChest"),
	SlowPotion = 5 UMETA(DisplayName = "SlowPotion"),
	LiveChicken = 6 UMETA(DisplayName = "LiveChicken"),
	Wolf = 7 UMETA(DisplayName = "Wolf"),
};
