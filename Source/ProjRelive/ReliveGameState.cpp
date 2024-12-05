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
	DOREPLIFETIME(AReliveGameState, CurrentSubGameMode);
	DOREPLIFETIME(AReliveGameState, PreviousSubGameMode);
	DOREPLIFETIME(AReliveGameState, IsTreasureHuntActive);
	DOREPLIFETIME(AReliveGameState, RemainingDefenseLife);
	DOREPLIFETIME(AReliveGameState, IsFreeMode);
}

void AReliveGameState::ChangeGameMode(EGameMode NewGameMode)
{
	PreviousGameMode = CurrentGameMode;
	CurrentGameMode = NewGameMode;
}

void AReliveGameState::ChangeSubGameMode(EGameMode NewGameMode)
{
	PreviousSubGameMode = CurrentSubGameMode;
	CurrentSubGameMode = NewGameMode;
}

void AReliveGameState::TriggerGameModeChange()
{
	GameModeChanged.Broadcast(CurrentGameMode);
}

void AReliveGameState::TriggerSubGameModeChange()
{
	SubGameModeChange.Broadcast(CurrentSubGameMode);
}
