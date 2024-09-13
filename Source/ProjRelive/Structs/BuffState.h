// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjRelive/Enums/EPlayerStats.h"
#include "BuffState.generated.h"

USTRUCT(BlueprintType)
struct FBuffState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuffs Buff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime DateTimeCasted;

	FBuffState()
	{
		Duration = -1;
		Buff = EBuffs::None;
	}
};