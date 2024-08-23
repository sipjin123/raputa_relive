// Fill out your copyright notice in the Description page of Project Settings.


#include "RelivePlayerController.h"

void ARelivePlayerController::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Log, TEXT("CONTROLLER BEGIN PLAY"));
	if (ReliveCharacter == nullptr)
	{
		ReliveCharacter = Cast<AActor>(GetPawn());
		//ReliveCharacter.RelivePlayerController = this;
		if (ReliveCharacter == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Player Cache FAILED!"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Player Cache Assigned!"));
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