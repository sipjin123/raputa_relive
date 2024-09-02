// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Enums/EPlayerStats.h"
#include "ProjRelive/Enums/EquipType.h"
#include "ProjRelive/Enums/PlayerCombatState.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "ProjRelive/Items/ItemAttachment.h"
#include "ItemDataContents.generated.h"

USTRUCT(BlueprintType)
struct FItemDataContents : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Data")
	int32 Id = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity = 0;
};

USTRUCT(Blueprintable)
struct FItemStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int32 Quantity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Duration = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Cooldown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	float Lifetime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	EBuffs BuffApplied = EBuffs::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	EDebuffs DebuffApplied = EDebuffs::None;
};

USTRUCT(Blueprintable)
struct FItemAssetData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Asset")
	UTexture2D* Icon;
};

USTRUCT(Blueprintable)
struct FItemStorageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Storage")
	bool IsStackable = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Storage")
	int32 MaxStackSize = 100;
};

USTRUCT(Blueprintable)
struct FItemTextData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText InteractionText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FText UsageText;
};


