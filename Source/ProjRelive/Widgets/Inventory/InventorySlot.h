// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjRelive/Items/ItemData.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
    FItemData ItemData;

	UFUNCTION(BlueprintCallable)
	void AssignData(FItemData ItemDataCache);
};
