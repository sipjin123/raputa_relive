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

}

void UWebSocketSubSystem::Deinitialize()
{
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d "), *FString(__FUNCTION__), __LINE__);

	Super::Deinitialize();
}

bool UWebSocketSubSystem::IsConnected()
{
	if (!WebSocket)
	{
		return false;
	}

	if (!WebSocket->IsConnected())
	{
		return false;
	}

	return true;
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
	WebSocket->OnMessageSent.AddDynamic(this, &UWebSocketSubSystem::OnMessageSent);
	WebSocket->OnMessageReceived.AddDynamic(this, &UWebSocketSubSystem::OnMessageReceived);

	WebSocket->ConnectToServer();

	WebSocket->AddToRoot();

	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d "), *FString(__FUNCTION__), __LINE__);
}

void UWebSocketSubSystem::SendDonateResutToServer(const FResponseDonateProduct& Result)
{
	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is not valid"), *FString(__FUNCTION__), __LINE__);
		return;
	}

	FString ResponseString;
	if (!FJsonObjectConverter::UStructToJsonObjectString(FResponseDonateProduct::StaticStruct(), &Result, ResponseString, 0, 0))
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d make struct failed"), *FString(__FUNCTION__), __LINE__);
		return;
	}

	WebSocket->SendMessageToServer(ResponseString);
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
	FResponseDonateProduct ResponseDonateProduct;

	FRequestDonateProduct RequestDonateProduct;
	if (!FJsonObjectConverter::JsonObjectStringToUStruct<FRequestDonateProduct>(Message, &RequestDonateProduct))
	{
		ResponseDonateProduct.iResult = 1;
		SendDonateResutToServer(ResponseDonateProduct);
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d On Broadcast Items msg(%s) ."), *FString(__FUNCTION__), __LINE__, *Message);
		return;
	}

	FDonatePlayerInfo DonateInfo;
	DonateInfo.VTuberId = RequestDonateProduct.sVTuberId;
	DonateInfo.ProdcutID = RequestDonateProduct.sProdcutID;
	DonateInfo.DonateMoney = RequestDonateProduct.fDonateMoney;
	DonateInfo.DonateMoneyTotalVTuber = RequestDonateProduct.fDonateMoneyTotalVTuber;
	DonateInfo.DonateMoneyTotalAll = RequestDonateProduct.fDonateMoneyTotalAll;
	DonateInfo.DonatePlayerName = RequestDonateProduct.sDonatePlayerName;
	DonateInfo.DonatePlayerID = RequestDonateProduct.sDonatePlayerID;
	DonateInfo.BagId = RequestDonateProduct.sBagId;

	OnRequestDonateProduct.Broadcast(DonateInfo);
}

void UWebSocketSubSystem::OnMessageSent(const FString& Message)
{
	UE_LOG(LogWebSocket, Log, TEXT("%s(): %d Send to server success: %s"), *FString(__FUNCTION__), __LINE__, *Message);
}
