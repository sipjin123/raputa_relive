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