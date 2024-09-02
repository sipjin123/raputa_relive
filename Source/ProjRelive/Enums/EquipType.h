#pragma once

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common = 0 UMETA(DisplayName = "Common"),
	Uncommon = 1 UMETA(DisplayName = "Uncommon"),
	Rare = 2 UMETA(DisplayName = "Rare"),
	Legendary = 3 UMETA(DisplayName = "Legendary"),
};

UENUM(BlueprintType)
enum class EItemEquipSlot : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	RightHand = 1 UMETA(DisplayName = "RightHand"),
	LeftHand = 2 UMETA(DisplayName = "LeftHand"),
	Back = 3 UMETA(DisplayName = "Back"),
	Front = 4 UMETA(DisplayName = "Front"),
	Head = 5 UMETA(DisplayName = "Head"),
	Mount = 6 UMETA(DisplayName = "Mount"),
	Orbit = 7 UMETA(DisplayName = "Orbit"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Invalid = 0 UMETA(DisplayName = "Invalid"),
	Offensive = 1 UMETA(DisplayName = "Offensive"),
	Defensive = 2 UMETA(DisplayName = "Defensive"),
	Special = 3 UMETA(DisplayName = "Special"),
};

struct EquipType
{
	
};
