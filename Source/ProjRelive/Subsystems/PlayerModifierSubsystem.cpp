// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModifierSubsystem.h"

UPlayerModifierSubsystem::UPlayerModifierSubsystem() {

}

void UPlayerModifierSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitEventCalledInBlueprint();
}
