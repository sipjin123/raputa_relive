#pragma once
#include "CoreMinimal.h"
#include "ItemAttachment.h"
#include "Engine/DataTable.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "ProjRelive/Enums/EPlayerStats.h"
#include "ProjRelive/Enums/EquipType.h"
#include "ProjRelive/Enums/PlayerCombatState.h"
#include "ItemData.generated.h"

USTRUCT(Blueprintable)
struct FItemStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int32 Quantity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Duration = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Cooldown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Lifetime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	EBuffs BuffApplied = EBuffs::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	EDebuffs DebuffApplied = EDebuffs::None;
};

USTRUCT(Blueprintable)
struct FItemAssetData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Asset")
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, Category="Asset")
	UStaticMesh* Mesh;
};

USTRUCT(Blueprintable)
struct FItemStorageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Storage")
	bool IsStackable = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Storage")
	int32 MaxStackSize = 100;
};

USTRUCT(Blueprintable)
struct FItemTextData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText InteractionText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText UsageText;
};

USTRUCT(Blueprintable)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Item Data")
	int32 Id = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EPowerupType PowerupType = EPowerupType::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EItemRarity ItemRarity = EItemRarity::Common;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item Data")
	FItemTextData ItemTextData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EItemType ItemType = EItemType::Invalid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item Data")
	FItemStats ItemStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Item Data")
	FItemAssetData ItemAssetData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Item Data")
	FItemStorageInfo ItemStorageInfo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AReliveActor> ActorClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AItemAttachment> ItemAttachmentClass;
};
