// Fill out your copyright notice in the Description page of Project Settings.


#include "RelivePlayerState.h"
#include "Net/UnrealNetwork.h"

ARelivePlayerState::ARelivePlayerState()
{
}

void ARelivePlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ARelivePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARelivePlayerState, CooldownData);
	DOREPLIFETIME(ARelivePlayerState, PlayerIndex);
}
