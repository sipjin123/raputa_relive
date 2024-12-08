#pragma once

#include "CoreMinimal.h"
#include "MessageProtocol.generated.h"


// Receive data from backend server
USTRUCT(BlueprintType)
struct FGotItemData
{
	GENERATED_BODY()

	UPROPERTY()
	FString priceId;

	UPROPERTY()
	int32 quantity;
};

USTRUCT(BlueprintType)
struct FPlayerGotItemData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGotItemData> itemsData;
};

// 物品配置相关， 物品价格
USTRUCT(BlueprintType)
struct FItemPrice
{
	GENERATED_BODY()

};

// VTuber 的相关配置 
USTRUCT(BlueprintType)
struct FVTuberInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString VTuberId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString VTuberName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* SpawnPoint;

};

USTRUCT(BlueprintType)
struct FFansDonation
{
	GENERATED_BODY()

	// 统一定义的  网红ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString vtuberId;

	UPROPERTY()
	TArray<FGotItemData> itemsData;
};


// Broadcast : 通知全部的 客户端， 产生了哪些物品
USTRUCT(BlueprintType)
struct FBroadcastCheckoutItems
{
	GENERATED_BODY()

	// 用于标识， 具体是哪个玩家获得的这个物品
	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	TArray<FString> AllItems;
};