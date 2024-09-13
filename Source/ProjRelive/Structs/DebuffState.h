// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjRelive/Enums/EPlayerStats.h"
#include "DebuffState.generated.h"

USTRUCT(BlueprintType)
struct FDebuffState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDebuffs Debuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime DateTimeCasted;

	FDebuffState()
	{
		Duration = -1;
		Debuff = EDebuffs::None;
	}
};