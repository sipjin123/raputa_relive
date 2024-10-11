// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerScoreData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerScoreData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUniqueNetIdRepl NetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerScore;

	FPlayerScoreData()
	{
	}
};