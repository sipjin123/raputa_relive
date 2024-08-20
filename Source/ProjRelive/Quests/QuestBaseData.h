// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestBaseData.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UQuestBaseData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int QuestId = 0;
	
	UPROPERTY(BlueprintReadWrite)
	FName QuestName = "";
	
	UPROPERTY(BlueprintReadWrite)
	FString QuestDescription = "";
};