// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"

DEFINE_LOG_CATEGORY(InstanceSubsystemLog);
UQuestSubsystem::UQuestSubsystem()
{
}

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(InstanceSubsystemLog, Log, TEXT("INITIALIZED INSTANCE SUBSYSTEM C++"));
	Super::Initialize(Collection);
	InitEventCalledInBlueprint();
}
