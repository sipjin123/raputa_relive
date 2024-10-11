// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoringData.generated.h"
/**
 *
 */

USTRUCT(BlueprintType)
struct FScoringData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUniqueNetIdRepl NetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameMode GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerupType PowerupType;

	FScoringData()
	{
	}
};