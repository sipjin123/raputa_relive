// Fill out your copyright notice in the Description page of Project Settings.


#include "ReliveGameState.h"
#include "Net/UnrealNetwork.h"

AReliveGameState::AReliveGameState() :
	TestInt(2)
{
}

void AReliveGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReliveGameState, IsSinglePlayer);
	DOREPLIFETIME(AReliveGameState, CurrentGameMode);
	DOREPLIFETIME(AReliveGameState, PreviousGameMode);
}

void AReliveGameState::ChangeGameMode(EGameMode NewGameMode)
{
	PreviousGameMode = CurrentGameMode;
	CurrentGameMode = NewGameMode;
	GameModeChanged.Broadcast(NewGameMode);
}
