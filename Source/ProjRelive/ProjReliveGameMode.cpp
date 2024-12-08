// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjReliveGameMode.h"
#include "ProjReliveCharacter.h"
#include "Player/RelivePlayerController.h"
#include "Subsystems/ReliveGameInstance.h"

#include "WebSocketSubSystem.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AProjReliveGameMode::AProjReliveGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AProjReliveGameMode::BeginPlay()
{
	Super::BeginPlay();

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

void AProjReliveGameMode::BindCallbackFromWebsocket()
{



}
