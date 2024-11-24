// Fill out your copyright notice in the Description page of Project Settings.

#include "RelivePlayerController.h"
#include "ProjRelive.h"
#include "ProjReliveCharacter.h"
#include "World/PlayerSpawnPoint.h"
#include "Subsystems/LoginSubSystem.h"

#include "Kismet/GameplayStatics.h"

ARelivePlayerController::ARelivePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARelivePlayerController::Client_CanSpawnAvatar_Implementation(const int32 SpawnPosIndex)
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

	int32 AvatarIndex = LoginSubSystem->GetCurrentSelectPawnIndex();
	AvatarIndex = AvatarIndex % SpawnCharacterPair.Num();
	Server_ReqSpawnAvatar(SpawnPosIndex, AvatarIndex);
}

void ARelivePlayerController::Server_ReqSpawnAvatar_Implementation(const int32 SpawnPosIndex, const int32 AvatarIndex)
{
	if (AllSpawnPoints.IsEmpty())
	{
		return;
	}

	int32 SpawnPos = SpawnPosIndex % AllSpawnPoints.Num();
	const FVector TempSpawnLocation = AllSpawnPoints[SpawnPos]->GetActorLocation();
	const FRotator TempSpawnRotation = AllSpawnPoints[SpawnPos]->GetActorRotation();

	AProjReliveCharacter* ControlledCharacter = Cast<AProjReliveCharacter>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		GetWorld(),
		SpawnCharacterPair[AvatarIndex],
		FTransform(TempSpawnRotation, TempSpawnLocation),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding,
		this));

	if (!ControlledCharacter)
	{
		return;
	}

	UGameplayStatics::FinishSpawningActor(ControlledCharacter, FTransform(TempSpawnRotation, TempSpawnLocation));
	Possess(ControlledCharacter);
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

	InitSpawnPoint();

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

void ARelivePlayerController::InitSpawnPoint()
{
	AllSpawnPoints.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPointClass, AllSpawnPoints);
	if (AllSpawnPoints.IsEmpty())
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d can not find APlayerSpawnPoint"), *FString(__FUNCTION__), __LINE__);
		return;
	}

	UE_LOG(LogProjRelive, Warning, TEXT("%s(): %d APlayerSpawnPoint num is: %d"), *FString(__FUNCTION__), __LINE__, AllSpawnPoints.Num());
}
