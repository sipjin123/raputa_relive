// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ProjRelive/Items/Chest.h"


DEFINE_LOG_CATEGORY(SpawnerISSLog);
USpawnerSubsystem::USpawnerSubsystem()
{
}

void USpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(SpawnerISSLog, Log, TEXT("INITIALIZED INSTANCE SUBSYSTEM C++"));
	Super::Initialize(Collection);
	InitEventCalledInBlueprint();
}

void USpawnerSubsystem::SpawnChest(FVector Location, int ForUserId) const
{
	AChest* NewProjectile = GetWorld()->SpawnActor<AChest>();
}
