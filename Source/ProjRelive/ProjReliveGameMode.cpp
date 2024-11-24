// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjReliveGameMode.h"
#include "ProjReliveCharacter.h"
#include "Player/RelivePlayerController.h"
#include "UObject/ConstructorHelpers.h"

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

	PS->Client_CanSpawnAvatar(AllControllers.Num() - 1);
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
