// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ProjRelive/Enums/PlayerCombatState.h>
#include "CooldownData.generated.h"

USTRUCT(BlueprintType)
struct FCooldownData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerupType PowerupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime DateTimeCasted;

	FCooldownData()
	{
		DateTimeCasted = FDateTime::Now();
		PowerupType = EPowerupType::None;
	}
};