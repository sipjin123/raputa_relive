#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomWebSocket.generated.h"


class IWebSocket;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionError, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnClosed, int32, StatusCode, const FString&, Reason, bool, bWasClean);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageSent, const FString&, Message);


/**
 * WebSocket Client
 */
UCLASS(BlueprintType)
class WEBSOCKET_API UCustomWebSocket final : public UObject
{
	GENERATED_UCLASS_BODY()
	

public:

	UPROPERTY(BlueprintAssignable)
	FOnConnected OnConnected;

	UPROPERTY(BlueprintAssignable)
	FOnConnectionError OnConnectionError;

	UPROPERTY(BlueprintAssignable)
	FOnClosed OnClosed;

	UPROPERTY(BlueprintAssignable)
	FOnMessageReceived OnMessageReceived;

	UPROPERTY(BlueprintAssignable)
	FOnMessageSent OnMessageSent;

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void Init();

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void SetServerURL(const FString& URL);

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	FString GetServerURL() const { return ServerURL; }

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void SetProtocols(const TArray<FString>& protocols);

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	TArray<FString> GetProtocols() const { return Protocols; }

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void SetHeaders(const TMap<FString, FString>& Headers);

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	TMap<FString, FString> GetHeaders() const { return UpgradeHeaders; }

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void ConnectToServer();

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void CloseConnection(int32 StatusCode = 1000, const FString& Reason = TEXT(""));

	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	bool IsConnected() const;
	
	UFUNCTION(BlueprintCallable, Category = "CustomWebSocket")
	void SendMessageToServer(const FString& Message);


private:

	UFUNCTION()
	void OnConnected_Internal();

	UFUNCTION()
	void OnConnectionError_Internal(const FString& Error);

	UFUNCTION()
	void OnClosed_Internal(int32 StatusCode, const FString& Reason, bool bWasClean);

	UFUNCTION()
	void OnMessageReceived_Internal(const FString& Message);

	UFUNCTION()
	void OnMessageSent_Internal(const FString& Message);

	TSharedPtr<IWebSocket> WebSocket = nullptr;
	FString ServerURL;
	TArray<FString> Protocols;
	TMap<FString, FString> UpgradeHeaders;

};
