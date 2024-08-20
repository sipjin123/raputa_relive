// Fill out your copyright notice in the Description page of Project Settings.


#include "ReliveUtilityBFL.h"

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