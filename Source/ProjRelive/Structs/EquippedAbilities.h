// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Enums/EPlayerStats.h"
#include <ProjRelive/Enums/PlayerCombatState.h>
#include <ProjRelive/Items/ItemData.h>
#include "EquippedAbilities.generated.h"

USTRUCT(BlueprintType)
struct FEquippedAbilities
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerupType PowerupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SlotOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime DateTimeCasted;

	FEquippedAbilities()
	{
		ItemId = -1;
		PowerupType = EPowerupType::None;
		ItemData = FItemData();
		DateTimeCasted = FDateTime::Now();
	}

	void ClearContent();
};