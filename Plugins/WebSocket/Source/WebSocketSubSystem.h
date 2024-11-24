#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dom/JsonValue.h"
#include "WebSocketSubSystem.generated.h"

class UCustomWebSocket;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnBroadcastCheckoutItems, const bool, bResult, const FString&, PlayerID, const TArray<FString>, AllItems);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGotAllItemData, const TArray<FGotItemData>, GotItemData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGetMessageFromBackend);


UCLASS(BlueprintType)
class WEBSOCKET_API UWebSocketSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "StWebSocket | WebSocketSubSystem")
	void InitWebSocket();

	UFUNCTION(BlueprintCallable, Category = "StWebSocket | WebSocketSubSystem")
	void InitWebSocketEx(UGameInstance * ins);

	UPROPERTY(BlueprintAssignable)
	FOnBroadcastCheckoutItems OnBroadcastCheckoutItems;

	UPROPERTY(BlueprintAssignable)
	FOnGotAllItemData OnGotAllItemData;

	UPROPERTY(BlueprintAssignable)
	FOnGetMessageFromBackend OnGetMessageFromBackend;

private:

	UCustomWebSocket* WebSocket = nullptr;

	UFUNCTION()
	void OnConnected();

	UFUNCTION()
	void OnConnectionError(const FString& Error);

	UFUNCTION()
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);

	UFUNCTION()
	void OnMessageReceived(const FString& Message);

	UFUNCTION()
	void OnMessageSent(const FString& Message);

	TMap<uint32, FString> PlayerInfo;

};
