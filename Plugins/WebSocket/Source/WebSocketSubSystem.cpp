#include "WebSocketSubSystem.h"
#include "Configuration/ServerConfig.h"
#include "CustomWebSocket.h"
#include "MessageProtocol.h"
#include "WebSocket.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void UWebSocketSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnStartGameInstance.AddUObject(this, &UWebSocketSubSystem::InitWebSocketEx);

	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d Deinitialize Steam Session GameInstance Subsystem."), *FString(__FUNCTION__), __LINE__);
}

void UWebSocketSubSystem::Deinitialize()
{
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d Deinitialize Steam Session GameInstance Subsystem."), *FString(__FUNCTION__), __LINE__);

	Super::Deinitialize();
}

void UWebSocketSubSystem::InitWebSocketEx(UGameInstance* ins)
{
	InitWebSocket();
}

void UWebSocketSubSystem::InitWebSocket()
{
	TArray<FString> Protocols = {TEXT("ws")};

	WebSocket = NewObject<UCustomWebSocket>();

	FString WebsockURL = UServerConfig::GetWebsocketURL();
	WebSocket->SetServerURL(WebsockURL);
	WebSocket->SetProtocols(Protocols);
	WebSocket->Init();

	WebSocket->OnConnected.AddDynamic(this, &UWebSocketSubSystem::OnConnected);
	WebSocket->OnConnectionError.AddDynamic(this, &UWebSocketSubSystem::OnConnectionError);
	WebSocket->OnClosed.AddDynamic(this, &UWebSocketSubSystem::OnClosed);
	WebSocket->OnMessageReceived.AddDynamic(this, &UWebSocketSubSystem::OnMessageReceived);

	WebSocket->ConnectToServer();

	WebSocket->AddToRoot();
}

void UWebSocketSubSystem::OnConnected()
{
	FString WebsockURL = UServerConfig::GetWebsocketURL();
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d websoket connect success url(%s) ."), *FString(__FUNCTION__), __LINE__, *WebsockURL);
}

void UWebSocketSubSystem::OnConnectionError(const FString& Error)
{
	FString WebsockURL = UServerConfig::GetWebsocketURL();
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d websoket connect error url(%s) and error=(%s) ."), *FString(__FUNCTION__), __LINE__, *WebsockURL, *Error);
}

void UWebSocketSubSystem::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	FString WebsockURL = UServerConfig::GetWebsocketURL();
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d websoket connect close url(%s) ."), *FString(__FUNCTION__), __LINE__, *WebsockURL);
}

void UWebSocketSubSystem::OnMessageReceived(const FString& Message)
{
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d On Broadcast Items msg(%s) ."), *FString(__FUNCTION__), __LINE__, *Message);

	FPlayerGotItemData PlayerGotItemData;
	if (!FJsonObjectConverter::JsonObjectStringToUStruct<FPlayerGotItemData>(Message, &PlayerGotItemData))
	{
		OnBroadcastCheckoutItems.Broadcast(false, FString(), TArray<FString>());
		return;
	}

	OnGetMessageFromBackend.Broadcast();
	OnGotAllItemData.Broadcast(PlayerGotItemData.itemsData);


	//FBroadcastCheckoutItems CheckoutItems;

	//OnBroadcastCheckoutItems.Broadcast(true, CheckoutItems.PlayerID, CheckoutItems.AllItems);
}

void UWebSocketSubSystem::OnMessageSent(const FString& Message)
{
	if (WebSocket != nullptr)
	{
		WebSocket->SendMessageToServer(Message);
	}
}
