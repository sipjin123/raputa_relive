// Fill out your copyright notice in the Description page of Project Settings.


#include "ReliveGameInstance.h"
#include "Net/UnrealNetwork.h"

void UReliveGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UReliveGameInstance, IsSinglePlayer);
}

void UReliveGameInstance::TestFunc()
{
}
