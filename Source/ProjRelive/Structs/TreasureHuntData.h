// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TreasureHuntData.generated.h"
/**
 *
 */

USTRUCT(BlueprintType)
struct FTreasureHuntData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUniqueNetIdRepl PlayerNetID;

	UPROPERTY(BlueprintReadWrite)
	TArray<int> UserGatheredItems;

	UPROPERTY(BlueprintReadWrite)
	int TotalPoints;

	FTreasureHuntData()
	{
	}
};