#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProjRelive/Enums/EPlayerStats.h"
#include "ItemData.generated.h"

UENUM()
enum class EItemRarity : uint8
{
	Common = 0 UMETA(DisplayName = "Common"),
	Uncommon = 1 UMETA(DisplayName = "Uncommon"),
	Rare = 2 UMETA(DisplayName = "Rare"),
	Legendary = 3 UMETA(DisplayName = "Legendary"),
};

UENUM()
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

UENUM()
enum class EItemType : uint8
{
	Invalid = 0 UMETA(DisplayName = "Invalid"),
	Offensive = 1 UMETA(DisplayName = "Offensive"),
	Defensive = 2 UMETA(DisplayName = "Defensive"),
	Special = 3 UMETA(DisplayName = "Special"),
};

USTRUCT()
struct FItemStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 Quantity = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	float Duration = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	float Cooldown = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	float Lifetime = 0;
	UPROPERTY(EditAnywhere, Category="Stats")
	EBuffs BuffApplied = EBuffs::None;
	UPROPERTY(EditAnywhere, Category="Stats")
	EDebuffs DebuffApplied = EDebuffs::None;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Asset")
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, Category="Asset")
	UStaticMesh* Mesh;
};

USTRUCT()
struct FItemStorageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Storage")
	bool IsStackable;
	UPROPERTY(EditAnywhere, Category="Storage")
	int32 MaxStackSize;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Text")
	FText Name;
	UPROPERTY(EditAnywhere, Category="Text")
	FText Description;
	UPROPERTY(EditAnywhere, Category="Text")
	FText InteractionText;
	UPROPERTY(EditAnywhere, Category="Text")
	FText UsageText;
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="Item Data")
	int32 Id;
	UPROPERTY(EditAnywhere, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity;

	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemRarity ItemRarity;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemTextData ItemTextData;
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemType ItemType;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemStats ItemStats;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemAssetData ItemAssetData;
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	FItemStorageInfo ItemStorageInfo;
};
