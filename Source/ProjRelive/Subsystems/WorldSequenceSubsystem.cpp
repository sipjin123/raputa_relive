// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSequenceSubsystem.h"

void UWorldSequenceSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	InitEventCalledInBlueprint();
}

void UWorldSequenceSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	if (InWorld.GetNetMode() == NM_Client)
	UE_LOG(LogTemp, Log, TEXT("World Begin PLay C++ as Client"));
	if (InWorld.GetNetMode() != NM_Client)
		UE_LOG(LogTemp, Log, TEXT("World Begin PLay C++ as Server"));
	Super::OnWorldBeginPlay(InWorld);
}
