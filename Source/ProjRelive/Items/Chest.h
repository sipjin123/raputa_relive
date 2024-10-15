// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include <ProjRelive/Structs/TreasureItemData.h>
#include "GameFramework/Actor.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "Chest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnChestItem);
UCLASS()
class PROJRELIVE_API AChest : public AReliveActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(BlueprintReadWrite)
	bool IsRandom = false;

	UPROPERTY(BlueprintReadWrite)
	FDataTableRowHandle ItemDataHandle;

	UPROPERTY(BlueprintReadWrite)
	FItemData ItemDataCache;

	UPROPERTY(BlueprintReadWrite)
	FTreasureItemData TreasureItemDataCache;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FSpawnChestItem SpawnChestItem;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnChestItemEvent();

	UPROPERTY(BlueprintReadWrite)
	AActor* PlayerTarget;
};
