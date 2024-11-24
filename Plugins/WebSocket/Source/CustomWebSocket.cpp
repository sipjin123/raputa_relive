#include "CustomWebSocket.h"
#include "WebSocket.h"

#include "IWebSocket.h"
#include "WebSocketsModule.h"

UCustomWebSocket::UCustomWebSocket(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCustomWebSocket::Init()
{
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, Protocols, UpgradeHeaders);

	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is invalid  "), ANSI_TO_TCHAR(__FUNCTION__), __LINE__);
		return;
	}

	WebSocket->OnConnected().AddUObject(this, &ThisClass::OnConnected_Internal);
	WebSocket->OnConnectionError().AddUObject(this, &ThisClass::OnConnectionError_Internal);
	WebSocket->OnClosed().AddUObject(this, &ThisClass::OnClosed_Internal);
	WebSocket->OnMessage().AddUObject(this, &ThisClass::OnMessageReceived_Internal);
	WebSocket->OnMessageSent().AddUObject(this, &ThisClass::OnMessageSent_Internal);
}

void UCustomWebSocket::SetServerURL(const FString& URL)
{
	ServerURL = URL;
}

void UCustomWebSocket::SetProtocols(const TArray<FString>& protocols)
{
	Protocols = protocols;
}

void UCustomWebSocket::SetHeaders(const TMap<FString, FString>& Headers)
{
	UpgradeHeaders = Headers;
}

void UCustomWebSocket::ConnectToServer()
{
	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is invalid  "), ANSI_TO_TCHAR(__FUNCTION__), __LINE__);
		return;
	}

	WebSocket->Connect();
}

void UCustomWebSocket::CloseConnection(int32 StatusCode, const FString& Reason)
{
	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is invalid  "), ANSI_TO_TCHAR(__FUNCTION__), __LINE__);
		return;
	}

	WebSocket->Close(StatusCode, Reason);
}

bool UCustomWebSocket::IsConnected() const
{
	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is invalid  "), ANSI_TO_TCHAR(__FUNCTION__), __LINE__);
		return false;
	}

	return WebSocket->IsConnected();
}

void UCustomWebSocket::SendMessageToServer(const FString& Message)
{
	if (!WebSocket)
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d WebSocket is invalid  "), ANSI_TO_TCHAR(__FUNCTION__), __LINE__);
		return;
	}

	WebSocket->Send(Message);
}

void UCustomWebSocket::OnConnected_Internal()
{
	OnConnected.Broadcast();
}

void UCustomWebSocket::OnConnectionError_Internal(const FString& Error)
{
	OnConnectionError.Broadcast(Error);
}

void UCustomWebSocket::OnClosed_Internal(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	OnClosed.Broadcast(StatusCode, Reason, bWasClean);
}

void UCustomWebSocket::OnMessageReceived_Internal(const FString& Message)
{
	OnMessageReceived.Broadcast(Message);
}

void UCustomWebSocket::OnMessageSent_Internal(const FString& Message)
{
	OnMessageSent.Broadcast(Message);
}
