// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Items/ItemData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <ProjRelive/Structs/TreasureItemData.h>
#include "ItemSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API UItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UItemSubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintImplementableEvent)
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

	UPROPERTY(BlueprintReadWrite)
	UDataTable* ItemsDataTable;
	UPROPERTY(BlueprintReadWrite)
	UDataTable* TreasureItemsDataTable;
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle DefaultItemRowHandle;
	 
	UFUNCTION(BlueprintCallable)
	FItemData RequestItemData(FDataTableRowHandle RowHandle);

	UFUNCTION(BlueprintCallable)
	FTreasureItemData RequestTreasureItemData(FDataTableRowHandle RowHandle);

	UFUNCTION(BlueprintCallable)
	FDataTableRowHandle RequestRandomDataHandle(bool isTreasureItem);
};
