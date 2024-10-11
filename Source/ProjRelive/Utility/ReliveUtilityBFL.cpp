// Fill out your copyright notice in the Description page of Project Settings.


#include "ReliveUtilityBFL.h"
#include "GameplayTagsManager.h"
#include <ProjRelive/ReliveGameState.h>
#include "Kismet/GameplayStatics.h"

UReliveGameInstance* UReliveUtilityBFL::ReliveGameInstance(UObject* WorldContextObject)
{
	UWorld* olderWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	UGameInstance* oldGI = UGameplayStatics::GetGameInstance(olderWorld);
	UReliveGameInstance* GI = Cast<UReliveGameInstance>(oldGI);
	if (GI)
	{
		return  GI;
	}
	return nullptr;
}

AReliveGameState* UReliveUtilityBFL::ReliveGameState(UObject* WorldContextObject)
{
	UWorld* olderWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	AGameStateBase* oldGI = olderWorld->GetGameState<AGameStateBase>();
	AReliveGameState* GI = Cast<AReliveGameState>(oldGI);
	if (GI)
	{
		return  GI;
	}
	return nullptr;
}

TArray<FGameplayTag> UReliveUtilityBFL::TagsInContainer(FGameplayTagContainer container)
{
	return container.GetGameplayTagArray();
	/*
	UGameplayTagsManager::Get().RequestAllGameplayTags(container, false);
	TArray<FGameplayTag> TagArray;
	container.GetGameplayTagArray(TagArray);
	return TagArray;*/
}
