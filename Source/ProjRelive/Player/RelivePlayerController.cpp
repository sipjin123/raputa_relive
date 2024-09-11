// Fill out your copyright notice in the Description page of Project Settings.


#include "RelivePlayerController.h"

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

ARelivePlayerController::ARelivePlayerController()
{

}

void ARelivePlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	OnPossessAcknowledge.Broadcast();
}
