// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ServerConfig.generated.h"

/**
 * some server info configuration
 */
#define ServerConfigPath TEXT("/Script/WebSocket.ServerConfig")

UCLASS(config = ServerConfig, defaultconfig, meta = (DisplayName = "Server Config"))
class WEBSOCKET_API UServerConfig : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static FString GetWebsocketURL();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static FString GetDedicatedServerIP();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static int32 GetDedicatedServerPort();

	// websocket URL configured in Editor
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	FString WebsocketURL;

	// Dedicated Server IP
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	FString DedicatedServerIP;

	// Dedicated Server Port
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	int32 DedicatedServerPort = 0;

private:

	static bool GetConfigFile(FConfigFile& ConfigFile);

};