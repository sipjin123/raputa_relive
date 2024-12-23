// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjReliveGameMode.h"
#include "ProjRelive.h"
#include "ProjReliveCharacter.h"
#include "RelivePlayerState.h"
#include "Player/RelivePlayerController.h"
#include "Subsystems/ReliveGameInstance.h"

#include "WebSocketSubSystem.h"
#include "MessageProtocol.h"
#include "Configuration/ServerConfig.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AProjReliveGameMode::AProjReliveGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

AProjReliveCharacter* AProjReliveGameMode::FindAvatartByVTuberId(const FString& VTuberId) const
{
	AProjReliveCharacter* TargetAvatar = nullptr;

	for (auto OnePC : AllControllers)
	{
		ARelivePlayerState* PS = OnePC->GetPlayerState<ARelivePlayerState>();
		if (PS && PS->VTuberID == VTuberId)
		{
			TargetAvatar = Cast<AProjReliveCharacter>(PS->GetPawn());
			return TargetAvatar;
		}
	}

	return TargetAvatar;
}

void AProjReliveGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitWebSocket();
}

void AProjReliveGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{


	Super::EndPlay(EndPlayReason);
}

void AProjReliveGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	ARelivePlayerController* PS = Cast<ARelivePlayerController>(NewPlayerController);
	if (!PS)
	{
		return;
	}

	AllControllers.Add(PS);

	PS->Client_CanSpawnAvatar();
}

void AProjReliveGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ARelivePlayerController* PS = Cast<ARelivePlayerController>(Exiting);
	if (!PS)
	{
		return;
	}

	AllControllers.Remove(PS);
}

FDonatePlayerInfo AProjReliveGameMode::GetTestDonatePlayerInfo(FString vtuberId, float DonationValue)
{
	FDonatePlayerInfo NewFDonatePlayerInfo;
	NewFDonatePlayerInfo.VTuberId = vtuberId;
	NewFDonatePlayerInfo.DonateMoney = DonationValue;
	return NewFDonatePlayerInfo;
}

void AProjReliveGameMode::InitWebSocket()
{
	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d "), *FString(__FUNCTION__), __LINE__);
		return;
	}

	UWebSocketSubSystem* WebsocketSubsystem = GI->GetSubsystem<UWebSocketSubSystem>();
	if (!WebsocketSubsystem)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d "), *FString(__FUNCTION__), __LINE__);
		return;
	}

	if (WebsocketSubsystem->IsConnected())
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d "), *FString(__FUNCTION__), __LINE__);
		return;
	}

	WebsocketSubsystem->InitWebSocket();
	WebsocketSubsystem->OnRequestDonateProduct.AddDynamic(this, &ThisClass::OnRequestDonate);
}

void AProjReliveGameMode::BroadcastAllDonationInfo(const FDonatePlayerInfo& DonateInfo)
{
	for (auto OnePC : AllControllers)
	{
		OnePC->Client_ReceiveDonation(DonateInfo);
	}
}

int32 AProjReliveGameMode::DealWithDonation(const FDonatePlayerInfo& DonateInfo)
{
	BroadcastAllDonationInfo(DonateInfo);
	TMap<int32, int32> DonationItems;
	int32 ErrorCode = 0;
	if (!UServerConfig::GetDonationItems(DonateInfo.ProdcutID, DonationItems))
	{
		ErrorCode = 2;
		return ErrorCode;
	}

	SpawnDonationItems(DonateInfo, DonationItems, ErrorCode);

	return ErrorCode;
}

void AProjReliveGameMode::OnRequestDonate(const FDonatePlayerInfo& DonateInfo)
{
	// do something game play notify 
	int32 ErrorCode = DealWithDonation(DonateInfo);
	if (ErrorCode != 0)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d sVTuberId: %s, sProdcutID: %s , DonatePlayerName: %s, ErrorCode: %d"), *FString(__FUNCTION__), __LINE__, *DonateInfo.VTuberId, *DonateInfo.ProdcutID, *DonateInfo.DonatePlayerName, ErrorCode);
	}

	// notify server if success
	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d sVTuberId: %s, sProdcutID: %s , DonatePlayerName: %s"), *FString(__FUNCTION__), __LINE__, *DonateInfo.VTuberId, *DonateInfo.ProdcutID, *DonateInfo.DonatePlayerName);
		return;
	}

	UWebSocketSubSystem* WebsocketSubsystem = GI->GetSubsystem<UWebSocketSubSystem>();
	if (!WebsocketSubsystem)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d sVTuberId: %s, sProdcutID: %s , DonatePlayerName: %s"), *FString(__FUNCTION__), __LINE__, *DonateInfo.VTuberId, *DonateInfo.ProdcutID, *DonateInfo.DonatePlayerName);
		return;
	}
	FResponseDonateProduct Response;
	Response.sDonatePlayerID = DonateInfo.DonatePlayerID;
	Response.iResult = ErrorCode;
	Response.sBagId = DonateInfo.BagId;
	WebsocketSubsystem->SendDonateResutToServer(Response);
}
