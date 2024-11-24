#include "WebSocket.h"

#define LOCTEXT_NAMESPACE "FWebSocket"


DEFINE_LOG_CATEGORY(LogWebSocket)

void FWebSocket::StartupModule()
{
}

void FWebSocket::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWebSocket, WebSocket)
