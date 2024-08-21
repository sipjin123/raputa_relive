// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggeredDoor.h"

void ATriggeredDoor::OnInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Called From C++"));
	IIInteractable::OnInteract_Implementation();
}

void ATriggeredDoor::OnInteractByActor_Implementation(const AReliveActor* RActorRef)
{
	if (RActorRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("On Interact by Actor Called From C++"));
		IIInteractable::OnInteractByActor(RActorRef);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Actor Reference"));
	}
}

void ATriggeredDoor::OpenDoor_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Door Called From C++"));
	OnDoorOpened.Broadcast();
}

void ATriggeredDoor::CloseDoor_Implementation()
{
	OnDoorClosed.Broadcast();	
}

