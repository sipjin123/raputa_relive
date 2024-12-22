// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ServerConfig.generated.h"


// 网红出生点配置
USTRUCT(BlueprintType)
struct FVTuberSpawnPoint
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FString VTuberId = "";

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FString VTuberName = "";

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	int32  SpawnIndex = -1;

};

// 根据 product ID 配置，相关的游戏内的物品ID
USTRUCT(BlueprintType)
struct FProductIdItems
{
	GENERATED_BODY()

	// key is product ID
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	FString ProdcutID;

	// key: 游戏内 ITEM id，  value：该 ITEM的数量
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TMap<int32, int32> AllItemsInfo;
};


/**
 * some server info configuration
 */
#define ServerConfigPath TEXT("/Script/WebSocket.ServerConfig")

UCLASS(config = ServerConfig, defaultconfig, meta = (DisplayName = "Server Config"))
class WEBSOCKET_API UServerConfig : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	static const UServerConfig& Get();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static FString GetWebsocketURL();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static FString GetDedicatedServerIP();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static int32 GetDedicatedServerPort();

	UFUNCTION(BlueprintCallable, Category = "Server Config")
	static bool GetDonationItems(const FString& ProductID, TMap<int32, int32>& SpawnItems);

	// websocket URL configured in Editor
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	FString WebsocketURL;

	// Dedicated Server IP
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	FString DedicatedServerIP;

	// Dedicated Server Port
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	int32 DedicatedServerPort = 0;

	// key: VTbuer ID
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	TArray<FVTuberSpawnPoint> AllVTubers;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Server Config")
	TArray<FProductIdItems> AllProductItems;

private:

	static bool GetConfigFile(FConfigFile& ConfigFile);

};
