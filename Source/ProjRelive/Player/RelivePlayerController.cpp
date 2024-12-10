// Fill out your copyright notice in the Description page of Project Settings.

#include "RelivePlayerController.h"
#include "ProjRelive.h"
#include "RelivePlayerState.h"
#include "ProjReliveCharacter.h"
#include "World/PlayerSpawnPoint.h"
#include "Subsystems/LoginSubSystem.h"

#include "Configuration/ServerConfig.h"
#include "MessageProtocol.h"

#include "Kismet/GameplayStatics.h"

ARelivePlayerController::ARelivePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARelivePlayerController::Client_ReceiveDonation_Implementation(const FDonatePlayerInfo& DonateInfo)
{
	UE_LOG(LogProjRelive, Error, TEXT("%s(): %d Receive Donation: %s %s"), *FString(__FUNCTION__), __LINE__, *DonateInfo.DonatePlayerID, *DonateInfo.DonatePlayerName);


}

void ARelivePlayerController::Client_CanSpawnAvatar_Implementation()
{
	if (SpawnCharacterPair.IsEmpty())
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	int32 SpawnPosIndex = LoginSubSystem->GetVTuberSpawnInfoById(LoginSubSystem->GetSelectedVTuberId()).SpawnIndex;
	int32 AvatarIndex = LoginSubSystem->GetCurrentSelectPawnIndex();
	AvatarIndex = AvatarIndex % SpawnCharacterPair.Num();

	Server_ReqSpawnAvatar(SpawnPosIndex, AvatarIndex, LoginSubSystem->GetSelectedVTuberId());
}

void ARelivePlayerController::Server_ReqSpawnAvatar_Implementation(const int32 SpawnPosIndex, const int32 AvatarIndex, const FString& ID)
{
	AllSpawnPoints.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPointClass, AllSpawnPoints);
	if (AllSpawnPoints.IsEmpty())
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d can not find APlayerSpawnPoint"), *FString(__FUNCTION__), __LINE__);
		return;
	}

	APlayerSpawnPoint* SpawnPoint = nullptr;
	for (auto OnePoint : AllSpawnPoints)
	{
		SpawnPoint = Cast<APlayerSpawnPoint>(OnePoint);
		if (!SpawnPoint)
		{
			continue;
		}

		if (SpawnPoint->SpawnIndex == SpawnPosIndex)
		{
			break;
		}
		else
		{
			continue;
		}
	}

	if (!SpawnPoint)
	{
		return;
	}

	const FVector TempSpawnLocation = SpawnPoint->GetActorLocation();
	const FRotator TempSpawnRotation = SpawnPoint->GetActorRotation();

	AProjReliveCharacter* ControlledCharacter = Cast<AProjReliveCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		GetWorld(),
		SpawnCharacterPair[AvatarIndex],
		FTransform(TempSpawnRotation, TempSpawnLocation),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
		this));

	if (!ControlledCharacter)
	{
		return;
	}

	UGameplayStatics::FinishSpawningActor(ControlledCharacter, FTransform(TempSpawnRotation, TempSpawnLocation));
	Possess(ControlledCharacter);

	ARelivePlayerState* PS = Cast<ARelivePlayerState>(ControlledCharacter->GetPlayerState());
	if (!PS)
	{
		return;
	}

	PS->VTuberID = ID;
	PS->UpdateCharacterName(ID);
}

void ARelivePlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	OnPossessAcknowledge.Broadcast();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeGameAndUI());
}

void ARelivePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ReliveCharacter == nullptr)
	{
		ReliveCharacter = Cast<AActor>(GetPawn());
		//ReliveCharacter.RelivePlayerController = this;
		if (ReliveCharacter == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Player Cache FAILED!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to assign Relive Character"));
	}
}
