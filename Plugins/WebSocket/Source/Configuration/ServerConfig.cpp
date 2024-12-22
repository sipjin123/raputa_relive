// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerConfig.h"
#include "WebSocket.h"

const UServerConfig& UServerConfig::Get()
{
	return *GetDefault<UServerConfig>();
}

UServerConfig::UServerConfig(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CategoryName = "ProjRelive";

	SectionName = "Server Config";
}

FString UServerConfig::GetWebsocketURL()
{
	const UServerConfig* Settings = GetDefault<UServerConfig>();

	FString RealWebsocketURL = Settings->WebsocketURL;

	FConfigFile Config;
	if (GetConfigFile(Config))
	{
		Config.GetString(ServerConfigPath, TEXT("WebsocketURL"), RealWebsocketURL);
	}

	return RealWebsocketURL;
}

FString UServerConfig::GetDedicatedServerIP()
{
	const UServerConfig* Settings = GetDefault<UServerConfig>();

	FString RealDedicatedServerIP = Settings->DedicatedServerIP;

	FConfigFile Config;
	if (GetConfigFile(Config))
	{
		Config.GetString(ServerConfigPath, TEXT("DedicatedServerIP"), RealDedicatedServerIP);
	}

	return RealDedicatedServerIP;
}

int32 UServerConfig::GetDedicatedServerPort()
{
	const UServerConfig* Settings = GetDefault<UServerConfig>();

	int32 RealDedicatedServerPort = Settings->DedicatedServerPort;

	FConfigFile Config;
	if (GetConfigFile(Config))
	{
		Config.GetInt(ServerConfigPath, TEXT("DedicatedServerPort"), RealDedicatedServerPort);
	}

	return RealDedicatedServerPort;
}

bool UServerConfig::GetDonationItems(const FString& ProductID, TMap<int32, int32>& SpawnItems)
{
	const UServerConfig* Settings = GetDefault<UServerConfig>();
	const TArray<FProductIdItems>& AllProductItems = Settings->AllProductItems;
	for (auto OneProduct : AllProductItems)
	{
		if (OneProduct.ProdcutID == ProductID)
		{
			SpawnItems = OneProduct.AllItemsInfo;
			return true;
		}
	}

	return false;
}

bool UServerConfig::GetConfigFile(FConfigFile& ConfigFile)
{
	FString ConfigPath = TEXT("DefaultServerConfig");
	if (!GConfig->LoadLocalIniFile(ConfigFile, *ConfigPath, false))
	{
		UE_LOG(LogWebSocket, Error, TEXT("%s(): %d Config/DefaultServerConfig.ini file isn't found!"), *FString(__FUNCTION__), __LINE__);
		return true;
	}

	return true;
}