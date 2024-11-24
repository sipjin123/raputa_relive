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


// Broadcast : ֪ͨȫ���� �ͻ��ˣ� ��������Щ��Ʒ
USTRUCT(BlueprintType)
struct FBroadcastCheckoutItems
{
	GENERATED_BODY()

	// ���ڱ�ʶ�� �������ĸ���һ�õ������Ʒ
	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	TArray<FString> AllItems;
};