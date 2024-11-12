// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ProjRelive/Enums/PlayerGameModeStates.h>
#include "GameModeSchedule.generated.h"
/**
 *
 */

USTRUCT(BlueprintType)
struct FGameModeSchedule
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GameModeIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameMode GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime TimeStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime TimeEnds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickRegistered;

	FGameModeSchedule()
	{
		GameModeIndex = -1;
		TickRegistered = -1;
		GameMode = EGameMode::None;
		TimeStarted = FDateTime::UtcNow();
		TimeEnds = FDateTime::UtcNow();
	}
};