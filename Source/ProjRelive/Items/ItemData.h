#pragma once
#include "CoreMinimal.h"
#include "ItemDataContents.h"
#include "ItemData.generated.h"

USTRUCT(Blueprintable)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	int32 Id = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EPowerupType PowerupType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EItemRarity ItemRarity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item Data")
	FItemTextData ItemTextData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	EItemType ItemType;
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
