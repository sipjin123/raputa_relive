// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterUtilityActor.h"

AMasterUtilityActor::AMasterUtilityActor()
{
	UE_LOG(LogTemp, Log, TEXT("INITIALIZED INSTANCE SUBSYSTEM C++"));

	/// GetOwner()->FindComponentByClass<UPlayerModifierComponent>();


	// Enum Loop
	/*
	for (EPowerupType myErrorType = EPowerupType::begin;
		myErrorType < EPowerupType::end;
		myErrorType = static_cast<EPowerupType>((size_t)myErrorType + 1))
	*/
	// Enum String
	// FString EnumAsString = UEnum::GetDisplayValueAsText(myErrorType).ToString();
}

void AMasterUtilityActor::BeginPlay()
{
	Super::BeginPlay();
}
