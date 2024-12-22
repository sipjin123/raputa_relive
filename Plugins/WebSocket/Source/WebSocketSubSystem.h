#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dom/JsonValue.h"
#include "WebSocketSubSystem.generated.h"

class UCustomWebSocket;
struct FDonatePlayerInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestDonateProduct, const FDonatePlayerInfo&, DonatePlayerInfo);


UCLASS(BlueprintType)
class WEBSOCKET_API UWebSocketSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "WebSocketSubSystem")
	bool IsConnected();

	UFUNCTION(BlueprintCallable, Category = "WebSocketSubSystem")
	void InitWebSocket();

	UFUNCTION(BlueprintCallable)
	void SendDonateResutToServer(const FResponseDonateProduct& Result);

	UPROPERTY(BlueprintAssignable)
	FOnRequestDonateProduct OnRequestDonateProduct;

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
