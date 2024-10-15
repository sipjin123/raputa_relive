// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "ProjRelive/Items/ItemDataContents.h"
#include "TreasureItemData.generated.h"

USTRUCT(Blueprintable)
struct FTreasureItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	int32 Id = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	FItemAssetData ItemAssetData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<AReliveActor> ActorClass;
};
