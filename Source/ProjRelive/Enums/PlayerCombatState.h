#pragma once

UENUM(BlueprintType)
enum class EPowerupType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Chicken = 1 UMETA(DisplayName = "Chicken"),
	Speed = 2 UMETA(DisplayName = "Speedup"),
	Shield = 3 UMETA(DisplayName = "Shield"),
	BaseballBat = 4 UMETA(DisplayName = "BaseballBat"),
	Landmine = 5 UMETA(DisplayName = "Landmine"),
	Bighead = 6 UMETA(DisplayName = "Bighead"),
	Invisibility = 7 UMETA(DisplayName = "Invisibility"),
	Invinsibility = 8 UMETA(DisplayName = "Invinsibility"),
	FanBomb = 9 UMETA(DisplayName = "FanBomb"),
	Teleporter = 10 UMETA(DisplayName = "Teleporter"),
	MissionScroll = 11 UMETA(DisplayName = "MissionScroll"),

	_COUNT,
	begin = 0,
	end = _COUNT,
};
